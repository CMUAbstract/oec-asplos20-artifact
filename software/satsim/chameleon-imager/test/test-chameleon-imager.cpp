// test-chameleon-imager.cpp
// Chameleon Imager class test file
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
#include <cstddef>      // size_t
#include <vector>       // vector

// satsim
#include <ChameleonImager.hpp> // ChameleonImager
#include <Job.hpp>             // Job
#include <Logger.hpp>          // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::ChameleonImager chameleonImager(
   7.25, satsim::ChameleonImager::PowerState::IDLE, &logger
  );
  chameleonImager.setWorkerId(1);
  satsim::ChameleonImager* ciClone = chameleonImager.clone();
  delete ciClone;
  // Set up jobs
  std::vector<satsim::Job*> jobs;
  jobs.push_back(new satsim::Job(0,3072,&logger));
  jobs.push_back(new satsim::Job(1,3072,&logger));
  jobs.push_back(new satsim::Job(2,3072,&logger));
  jobs.push_back(new satsim::Job(3,3072,&logger));
  size_t nextJob = 0;
  // Simulation loop
  size_t microseconds = 0;
  // Each iteration is 1 us
  for(size_t i=0; i<5000000; i++) {
    if(i%10000==0) {
      chameleonImager.logMeasurement(
       "voltage-v",static_cast<double>(i)/1000000.0,chameleonImager.getVoltage()
      );
      chameleonImager.logMeasurement(
       "current-a",static_cast<double>(i)/1000000.0,chameleonImager.getCurrent()
      );
    }
    if(i%1000000==0) {
      chameleonImager.dequeImage();
    }
    if(i%1500000==0) {
      jobs.at(nextJob)->claimTasks(1,3072);
      chameleonImager.addClaimedJob(jobs.at(nextJob));
      nextJob++;
    }
    chameleonImager.setVoltage(chameleonImager.getVoltage()-0.000001);
    chameleonImager.update(1.0e-6);
    microseconds+=1;
  }
  // Clean up jobs
  for(size_t i=0; i<jobs.size(); i++) {
    delete jobs.at(i);
  }
  // Log
  logger.exportCsvs("../test");
  return 0;
}
