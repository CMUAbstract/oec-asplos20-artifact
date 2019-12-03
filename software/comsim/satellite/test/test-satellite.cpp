// test-satellite.cpp
// Satellite class test file
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
#include <array>         // array
#include <cstddef>       // size_t
#include <cstdlib>       // exit, EXIT_SUCCESS
#include <string>        // to_string

// satsim
#include <DateTime.hpp>  // DateTimeISO8601
#include <Log.hpp>       // Log
#include <LogLevel.hpp>  // LogLevel
#include <Satellite.hpp> // Satellite

int main(int argc, char** argv) {
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::INFO};
  comsim::Log log(levels,"../test");
  comsim::DateTime dateTime(1980,10,01,23,41,24,113759999);
  comsim::Satellite satellite("../data/test.tle",&dateTime,&log);
  for(size_t i=0; i<5; i++) {
    std::array<double,3> eciPosn = satellite.getECIPosn();
    log.meas(
     comsim::LogLevel::INFO, dateTime.toString(), "x-km",
     std::to_string(eciPosn.at(0))
    );
    log.meas(
     comsim::LogLevel::INFO, dateTime.toString(), "y-km",
     std::to_string(eciPosn.at(1))
    );
    log.meas(
     comsim::LogLevel::INFO, dateTime.toString(), "z-km",
     std::to_string(eciPosn.at(2))
    );
    dateTime.update(6,0,0,0);
    satellite.update(6,0,0,0);
  }
  // Write out logs
  log.writeAll();
  std::exit(EXIT_SUCCESS);
}
