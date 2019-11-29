// test-jetson-tx2.cpp
// Jetson TX2 class test file
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
#include <cstddef>       // size_t
#include <vector>        // vector

// satsim
#include <JetsonTX2.hpp> // JetsonTX2
#include <Logger.hpp>    // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::JetsonTX2 jetsonTX2(
   7.25, satsim::JetsonTX2::PowerState::IDLE, &logger
  );
  jetsonTX2.setWorkerId(1);
  jetsonTX2.logEvent(
   "jetson-"+std::to_string(jetsonTX2.getWorkerId())+"-idle-start",0.0
  );
  satsim::JetsonTX2* jtClone = jetsonTX2.clone();
  delete jtClone;
  // Set up jobs
  std::vector<satsim::Job*> jobs;
  jobs.push_back(new satsim::Job(0,32,&logger));
  jobs.push_back(new satsim::Job(1,32,&logger));
  jobs.push_back(new satsim::Job(2,32,&logger));
  jobs.push_back(new satsim::Job(3,32,&logger));
  size_t nextJob = 0;
  // Simulation loop
  size_t microseconds = 0;
  // Each iteration is 1 us
  for(size_t i=0; i<5000000; i++) {
    if(i%10000==0) {
      jetsonTX2.logMeasurement(
       "voltage-v",static_cast<double>(i)/1000000.0,jetsonTX2.getVoltage()
      );
      jetsonTX2.logMeasurement(
       "current-a",static_cast<double>(i)/1000000.0,jetsonTX2.getCurrent()
      );
    }
    if(i%1500000==0) {
      jobs.at(nextJob)->claimTasks(1,32);
      jetsonTX2.addClaimedJob(jobs.at(nextJob));
      nextJob++;
    }
    jetsonTX2.setVoltage(jetsonTX2.getVoltage()-0.000001);
    jetsonTX2.update(1.0e-6);
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
