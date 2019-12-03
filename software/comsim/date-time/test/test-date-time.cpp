// test-date-time.cpp
// DateTime class test file
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

// comsim
#include <constants.hpp> // constants
#include <DateTime.hpp>  // DateTime
#include <Log.hpp>       // Log
#include <LogLevel.hpp>  // LogLevel

int main(int argc, char** argv) {
  // Setup
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::TRACE};
  comsim::Log log(levels,"../test");
  // J2000
  comsim::DateTime j2000(2000, 1, 1,12, 0, 0,0);
  log.evnt(comsim::LogLevel::TRACE,j2000.toString(),"J2000");
  // Write logs
  log.writeAll();
  return 0;
}
