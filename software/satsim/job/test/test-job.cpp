// test-job.cpp
// Job class test file
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
