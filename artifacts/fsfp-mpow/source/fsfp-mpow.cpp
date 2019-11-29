// fsfp-mpow.cpp
// Frame-spaced, frame-parallel more power
//
// Written by Bradley Denby
// Other contributors: None
//
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication with this
// software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Standard library
#include <algorithm>           // max
#include <cmath>               // floor
#include <cstddef>             // size_t
#include <cstdint>             // exit, EXIT_SUCCESS, EXIT_FAILURE
#include <cstdlib>             // atoi
#include <iomanip>             // setw, setprecision, setfill
#include <ios>                 // fixed
#include <iostream>            // cout
#include <ostream>             // endl
#include <sstream>             // ostringstream

// satsim
#include <Capacitor.hpp>       // Capacitor
#include <ChameleonImager.hpp> // ChameleonImager
#include <EHSatellite.hpp>     // EHSatellite
#include <EHSystem.hpp>        // EHSystem
#include <EnergyConsumer.hpp>  // EnergyConsumer
#include <EnergyHarvester.hpp> // EnergyHarvester
#include <JetsonTX2.hpp>       // JetsonTX2
#include <Job.hpp>             // Job
#include <Logger.hpp>          // Logger
#include <MAIAdacs.hpp>        // MAIAdacs
#include <Orbit.hpp>           // Orbit
#include <Satellite.hpp>       // Satellite
#include <SimpleSolarCell.hpp> // SimpleSolarCell

int main(int argc, char** argv) {
  size_t tasksPerJob   = 3072;
  size_t pipelineDepth = 1;
  // Parse command line argument(s)
  if(argc!=2) {
    std::cout << "Usage: ./" << argv[0] << " int"
              << std::endl
              << "  int: pipeline depth (minimum 1)"
              << std::endl;
    std::exit(EXIT_FAILURE);
  } else {
    pipelineDepth = std::max(1,std::atoi(argv[1]));
  }
  // Set up logger
  satsim::Logger logger("s");
  // Set up jobs
  size_t gtfCount = 1642;
  std::vector<satsim::Job*> gtfs;
  for(size_t i=0; i<gtfCount; i++) {
    gtfs.push_back(new satsim::Job(i,tasksPerJob));
  }
  // Build one satellite in the pipeline to start
  const double PI = satsim::Orbit::TAU/2.0;
  const double radPerGtf = PI/gtfs.size();
  std::vector<satsim::EHSatellite*> ehsatellites;
  // Orbit: 400 km altitude polar orbit (93 min period = 5580.0 sec)
  // For FSFP, satellites are separated in radial position
  satsim::Orbit orbit(5580.0, 0.0);
  // Energy harvester
  // Azur Space 3G30A 2.5E14; three in series of two cells in parallel (6 ct.)
  double sscVmp_V = 7.0290;
  double sscCmp_A = 2.0*1.0034;
  double nodeVoltage_V = sscVmp_V; // Start at maximum node voltage
  satsim::EnergyHarvester* simpleSolarCell =
   new satsim::SimpleSolarCell(sscVmp_V, sscCmp_A, nodeVoltage_V, &logger);
  simpleSolarCell->setWorkerId(0);
  // Energy storage
  // AVX SuperCapacitor SCMR22L105M; five in parallel
  // Cap_V: nodeVoltage_V-sscCmp_A*esr_Ohm is max valid voltage for this model
  // Assuming sim starts with this Cap_V, charge is Cap_V*capacity_F
  double capacity_F = 5.0;
  double esr_Ohm    = 0.168;
  double charge_C = (nodeVoltage_V-sscCmp_A*esr_Ohm)*capacity_F;
  satsim::Capacitor capacitor(capacity_F,esr_Ohm,charge_C,sscCmp_A,&logger);
  // Minimal energy harvesting system
  satsim::EHSystem ehsystem(*simpleSolarCell, capacitor, &logger);
  // Clean up energy harvester
  delete simpleSolarCell;
  // Energy consumer: Jetson TX2
  satsim::JetsonTX2 jetsonTX2(
   nodeVoltage_V, satsim::JetsonTX2::PowerState::IDLE, &logger
  );
  jetsonTX2.setWorkerId(0);
  jetsonTX2.logEvent(
   "jetson-"+std::to_string(jetsonTX2.getWorkerId())+"-idle-start",0.0
  );
  ehsystem.addEnergyConsumer(jetsonTX2);
  // Energy consumer: Chameleon imager
  satsim::ChameleonImager chameleonImager(
   nodeVoltage_V, satsim::ChameleonImager::PowerState::IDLE, &logger
  );
  chameleonImager.setWorkerId(0);
  //chameleonImager.logEvent(
  // "chamgr-"+std::to_string(chameleonImager.getWorkerId())+"-idle-start",0.0
  //);
  ehsystem.addEnergyConsumer(chameleonImager);
  // Energy consumer: MAI ADACS
  satsim::MAIAdacs maiadacs(
   nodeVoltage_V, satsim::MAIAdacs::PowerState::NADIR, &logger
  );
  ehsystem.addEnergyConsumer(maiadacs);
  // Push back new energy harvesting satellite
  ehsatellites.push_back(new satsim::EHSatellite(orbit, ehsystem, &logger));
  // Run simulation
  //const double STEP = 0.00314159265358979323846;
  //double thresh     = 0.00314159265358979323846;
  //double percent    = 0.0;
  double simTime_sec = 0.0;
  bool simulate = true;
  while(simulate) {
    // Prove that the simulation should still run
    simulate = false;
    // Run simulation for each satellite
    for(size_t i=0; i<ehsatellites.size(); i++) {
      satsim::EHSatellite* ehsPtr = ehsatellites.at(i);
      double ehsPosn = ehsPtr->getOrbit().getPosn();
      // if posn < PI check to see if new jobs are added
      if(ehsPosn<PI) {
        simulate = true;
        std::vector<satsim::EnergyConsumer*> ecs = ehsPtr->getEnergyConsumers();
        satsim::JetsonTX2*       jtPtr =
         dynamic_cast<satsim::JetsonTX2*>(ecs.at(0));
        satsim::ChameleonImager* ciPtr =
         dynamic_cast<satsim::ChameleonImager*>(ecs.at(1));
        satsim::Job* jobPtr = gtfs.at(std::floor(ehsPosn/radPerGtf));
        // Push job onto ChameleonImager if IDLE and readyImages is empty and
        // the ground track frame has unclaimed tasks
        if(ciPtr->isIdle() && !ciPtr->hasImage() &&
           jobPtr->getUnclaimedTaskCount()>0) {
          // For FSFP, all tasks are claimed
          jobPtr->claimTasks(ciPtr->getWorkerId(), tasksPerJob);
          ciPtr->addClaimedJob(jobPtr);
        }
        // Transfer job from ChameleonImager to Jetson if
        // ChameleonImager has completed work and Jetson is low on work
        if(ciPtr->hasImage() && jtPtr->getClaimedJobCount()==0) {
          while(ciPtr->hasImage()) {
            jtPtr->addClaimedJob(ciPtr->dequeImage());
          }
        }
        // Clean up
        jtPtr  = NULL;
        ciPtr  = NULL;
        jobPtr = NULL;
        for(size_t j=0; j<ecs.size(); j++) {
          ecs.at(j) = NULL;
        }
        ecs.clear();
        // Update
        ehsPtr->update(2.0e-5);
      }
      // otherwise, continue updating if Jetson is not idle
      else {
        std::vector<satsim::EnergyConsumer*> ecs = ehsPtr->getEnergyConsumers();
        satsim::JetsonTX2* jtPtr = dynamic_cast<satsim::JetsonTX2*>(ecs.at(0));
        if(!jtPtr->isIdle()) {
          simulate = true;
          // Update
          ehsPtr->update(2.0e-5);
        }
        // Clean up
        jtPtr  = NULL;
        for(size_t j=0; j<ecs.size(); j++) {
          ecs.at(j) = NULL;
        }
        ecs.clear();
      }
      // Clean up
      ehsPtr = NULL;
    }
    simTime_sec += 2.0e-5;
    // if the back satellite is past the initial ground track frame
    // then add the next satellite if the pipeline hasn't been finished
    if(ehsatellites.size()<pipelineDepth &&
       ehsatellites.back()->getOrbit().getPosn()>=radPerGtf) {
      // Orbit: 400 km altitude polar orbit (93 min period = 5580.0 sec)
      // For FSFP, satellites are separated in radial position
      satsim::Orbit orbit(5580.0, 0.0);
      // Energy harvester
      // Azur Space 3G30A 2.5E14; 3 in series of 2 cells in parallel (6 ct.)
      satsim::EnergyHarvester* simpleSolarCell =
       new satsim::SimpleSolarCell(sscVmp_V, sscCmp_A, nodeVoltage_V, &logger);
      simpleSolarCell->setWorkerId(ehsatellites.size());
      // Energy storage
      // AVX SuperCapacitor SCMR22L105M; five in parallel
      // Cap_V: nodeVoltage_V-sscCmp_A*esr_Ohm is max valid voltage for model
      // Assuming sim starts with this Cap_V, charge is Cap_V*capacity_F
      satsim::Capacitor capacitor(capacity_F,esr_Ohm,charge_C,sscCmp_A,&logger);
      // Minimal energy harvesting system
      satsim::EHSystem ehsystem(*simpleSolarCell, capacitor, &logger);
      // Clean up energy harvester
      delete simpleSolarCell;
      // Energy consumer: Jetson TX2
      satsim::JetsonTX2 jetsonTX2(
       nodeVoltage_V, satsim::JetsonTX2::PowerState::IDLE, &logger
      );
      jetsonTX2.setWorkerId(ehsatellites.size());
      jetsonTX2.setSimTime(simTime_sec);
      jetsonTX2.logEvent(
       "jetson-"+std::to_string(jetsonTX2.getWorkerId())+"-idle-start",
       simTime_sec
      );
      ehsystem.addEnergyConsumer(jetsonTX2);
      // Energy consumer: Chameleon imager
      satsim::ChameleonImager chameleonImager(
       nodeVoltage_V, satsim::ChameleonImager::PowerState::IDLE, &logger
      );
      chameleonImager.setWorkerId(ehsatellites.size());
      chameleonImager.setSimTime(simTime_sec);
      //chameleonImager.logEvent(
      // "chamgr-"+std::to_string(chameleonImager.getWorkerId())+"-idle-start",
      // simTime_sec
      //);
      ehsystem.addEnergyConsumer(chameleonImager);
      // Energy consumer: MAI ADACS
      satsim::MAIAdacs maiadacs(
       nodeVoltage_V, satsim::MAIAdacs::PowerState::NADIR, &logger
      );
      ehsystem.addEnergyConsumer(maiadacs);
      // Push back new energy harvesting satellite
      ehsatellites.push_back(new satsim::EHSatellite(orbit, ehsystem, &logger));
    }
    // Progress report
    //if(ehsatellites.back()->getOrbit().getPosn() <= 0.75*satsim::Orbit::TAU &&
    //   ehsatellites.back()->getOrbit().getPosn() >= thresh) {
    //  thresh += STEP;
    //  percent += 0.1;
    //  std::cout << std::setw(5) << std::fixed << std::setprecision(1)
    //            << percent << "% complete"
    //            << std::endl;
    //}
  }
  // Simulation is over, all Jetsons are in idle mode
  for(size_t i=0; i<ehsatellites.size(); i++) {
    satsim::EHSatellite* ehsPtr = ehsatellites.at(i);
    std::vector<satsim::EnergyConsumer*> ecs = ehsPtr->getEnergyConsumers();
    satsim::JetsonTX2* jtPtr = dynamic_cast<satsim::JetsonTX2*>(ecs.at(0));
    jtPtr->logEvent(
     "jetson-"+std::to_string(jtPtr->getWorkerId())+"-idle-stop",
     jtPtr->getSimTime()
    );
    // Clean up
    jtPtr  = NULL;
    for(size_t j=0; j<ecs.size(); j++) {
      ecs.at(j) = NULL;
    }
    ecs.clear();
    ehsPtr = NULL;
  }
  // Write out logs
  std::ostringstream oss;
  oss << "../logs/" << std::setfill('0') << std::setw(3)
      << std::atoi(argv[1]);
  logger.exportCsvs(oss.str());
  // Clean up each satellite in the pipeline
  for(size_t i=0; i<ehsatellites.size(); i++) {
    delete ehsatellites.at(i);
  }
  // Clean up jobs
  for(size_t i=0; i<gtfs.size(); i++) {
    delete gtfs.at(i);
  }
  std::exit(EXIT_SUCCESS);
}
