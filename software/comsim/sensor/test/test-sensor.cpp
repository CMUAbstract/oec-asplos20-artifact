// test-sensor.cpp
// Sensor class test file
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
#include <array>        // array
#include <cstddef>      // size_t
#include <cstdlib>      // exit, EXIT_SUCCESS
#include <string>       // to_string

// satsim
#include <DateTime.hpp> // DateTime
#include <Log.hpp>      // Log
#include <LogLevel.hpp> // LogLevel
#include <Sensor.hpp>   // Sensor

int main(int argc, char** argv) {
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::INFO};
  comsim::Log log(levels,"../test");
  comsim::DateTime globalTime(1980,10,01,23,41,24,113759999);
  comsim::Sensor sensor(&globalTime,0,&log);
  sensor.setBitsPerSense(40000000);
  for(size_t i=0; i<100; i++) {
    std::array<double,3> eciPosn = {static_cast<double>(i),0.0,0.0};
    sensor.setECIPosn(eciPosn);
    if(i%10==0) {
      sensor.triggerSense();
    }
    globalTime.update(1,0,0,0);
    sensor.update(1,0,0,0);
    log.meas(
     comsim::LogLevel::INFO, globalTime.toString(), "buffer-MB",
     std::to_string(sensor.getBitsBuffered()/8.0/1.0e6)
    );
  }
  sensor.drainBuffer(80000000);
  log.meas(
   comsim::LogLevel::INFO, globalTime.toString(), "buffer-MB",
   std::to_string(sensor.getBitsBuffered()/8.0/1.0e6)
  );
  // Write out logs
  log.writeAll();
  std::exit(EXIT_SUCCESS);
}
