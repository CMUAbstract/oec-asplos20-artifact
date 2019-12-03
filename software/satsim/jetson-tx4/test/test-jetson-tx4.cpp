// test-jetson-tx4.cpp
// Jetson TX4 class test file
//
// Copyright 2019 Bradley Denby
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at <http://www.apache.org/licenses/LICENSE-2.0>.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// Standard library
#include <cstddef>       // size_t
#include <vector>        // vector

// satsim
#include <JetsonTX4.hpp> // JetsonTX4
#include <Logger.hpp>    // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::JetsonTX4 jetsonTX4(
   7.25, satsim::JetsonTX4::PowerState::IDLE, &logger
  );
  jetsonTX4.setWorkerId(1);
  jetsonTX4.logEvent(
   "jetson-"+std::to_string(jetsonTX4.getWorkerId())+"-idle-start",0.0
  );
  satsim::JetsonTX4* jtClone = jetsonTX4.clone();
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
      jetsonTX4.logMeasurement(
       "voltage-v",static_cast<double>(i)/1000000.0,jetsonTX4.getVoltage()
      );
      jetsonTX4.logMeasurement(
       "current-a",static_cast<double>(i)/1000000.0,jetsonTX4.getCurrent()
      );
    }
    if(i%1500000==0) {
      jobs.at(nextJob)->claimTasks(1,32);
      jetsonTX4.addClaimedJob(jobs.at(nextJob));
      nextJob++;
    }
    jetsonTX4.setVoltage(jetsonTX4.getVoltage()-0.000001);
    jetsonTX4.update(1.0e-6);
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
