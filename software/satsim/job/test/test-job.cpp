// test-job.cpp
// Job class test file
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
#include <cstddef>    // size_t

// satsim
#include <Job.hpp>    // Job
#include <Logger.hpp> // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::Job job(0, 3072, &logger);
  satsim::Job* jClone = job.clone();
  delete jClone;
  // Simulation loop
  size_t microseconds = 0;
  // Each iteration is 1 us
  job.claimTasks(0,1536);
  job.claimTasks(1,1536);
  for(size_t i=0; i<2500000; i++) {
    if((i+1)%44870==0) {
      job.completeTask(0);
      job.logEvent("worker-0-task-completion",static_cast<double>(i/1000000.0));
      job.completeTask(1);
      job.logEvent("worker-1-task-completion",static_cast<double>(i/1000000.0));
    }
    job.update(1.0e-6);
    microseconds+=1;
  }
  logger.exportCsvs("../test");
  return 0;
}
