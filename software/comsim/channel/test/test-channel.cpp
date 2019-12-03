// test-channel.cpp
// Channel class test file
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
#include <cstdlib>      // exit, EXIT_SUCCESS
#include <iostream>     // cout
#include <ostream>      // endl

// comsim
#include <Channel.hpp>  // Channel
#include <DateTime.hpp> // DateTime
#include <Log.hpp>      // Log
#include <LogLevel.hpp> // LogLevel
#include <Receive.hpp>  // Receive
#include <Transmit.hpp> // Transmit

int main(int argc, char** argv) {
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::TRACE};
  comsim::Log log(levels,"../test");
  comsim::DateTime globalTime(1995,11,18,12,46, 0,0);
  std::array<double,3> posn = {-4400.594, 1932.870, 4760.712};
  comsim::Transmit transmit(posn, 15.0, -1.0, 6.0, &globalTime, 1, &log);
  comsim::Receive receive(posn, 6.0, &globalTime, 2, &log);
  comsim::Channel channel(
   &transmit, &receive, 8.0e9, 20.0e6, &globalTime, &log
  );
  std::cout << "Success; test complete"
            << std::endl;
  std::exit(EXIT_SUCCESS);
}
