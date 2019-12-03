// test-logger.cpp
// Logger class test file
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
#include <Logger.hpp> // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  // Each iteration is 1 ms
  for(size_t i=0; i<5000; i++) {
    if(i%100==0) {
      logger.logMeasurement(
       "voltage-V", 0.001*static_cast<double>(i), 0.0024*static_cast<double>(i)
      );
      logger.logMeasurement(
       "current-A", 0.001*static_cast<double>(i), 0.00002*static_cast<double>(i)
      );
    }
    if(i%1000==0) {
      logger.logEvent("second",0.001*static_cast<double>(i));
    }
  }
  logger.exportCsvs("../test");
  return 0;
}
