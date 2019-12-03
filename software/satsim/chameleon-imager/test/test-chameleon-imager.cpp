// test-chameleon-imager.cpp
// Chameleon Imager class test file
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
