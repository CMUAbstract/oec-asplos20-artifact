// test-log.cpp
// Log class test file
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
#include <string>       // to_string

// comsim
#include <Log.hpp>      // Log
#include <LogLevel.hpp> // LogLevel

int main(int argc, char** argv) {
  std::vector<comsim::LogLevel> levels =
   {comsim::LogLevel::INFO,comsim::LogLevel::ERROR};
  comsim::Log log(levels,"../test");
  std::string dateTime = "2019-06-18T11:17:";
  for(size_t i=0; i<60; i++) {
    log.meas(
     comsim::LogLevel::INFO, dateTime+std::to_string(i)+".0",
     "voltage-V", std::to_string(0.0024*static_cast<double>(i))
    );
    log.meas(
     comsim::LogLevel::TRACE, dateTime+std::to_string(i)+".0",
     "current-A", std::to_string(0.0002*static_cast<double>(i))
    );
    log.evnt(
     comsim::LogLevel::INFO, dateTime+std::to_string(i)+".0", "tick"
    );
  }
  log.writeAll();
  return 0;
}
