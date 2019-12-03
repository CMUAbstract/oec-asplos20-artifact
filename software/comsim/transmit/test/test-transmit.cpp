// test-transmit.cpp
// Transmit class test file
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

// comsim
#include <DateTime.hpp> // DateTime
#include <Log.hpp>      // Log
#include <LogLevel.hpp> // LogLevel
#include <Transmit.hpp> // Transmit

int main(int argc, char** argv) {
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::TRACE};
  comsim::Log log(levels,"../test");
  comsim::DateTime dateTime(1995,11,18,12,46, 0,0);
  std::array<double,3> posn = {-4400.594, 1932.870, 4760.712};
  comsim::Transmit transmit(posn, 15.0, -1.0, 6.0, &dateTime, 1, &log);
  log.evnt(comsim::LogLevel::TRACE, "Constructor", "test-success");
  std::array<double,3> testPosn = transmit.getPosn();
  log.evnt(comsim::LogLevel::TRACE, "getPosn", "test-success");
  double testPower = transmit.getPower();
  log.meas(
   comsim::LogLevel::TRACE, dateTime.toString(), "power",
   std::to_string(testPower)
  ); // expected value: 15.0
  double testLineLossFactor = transmit.getLineLoss();
  log.meas(
   comsim::LogLevel::TRACE, dateTime.toString(), "line-loss",
   std::to_string(testLineLossFactor)
  ); // expected value: 0.794
  double testGainFactor = transmit.getGain();
  log.meas(
   comsim::LogLevel::TRACE, dateTime.toString(), "gain",
   std::to_string(testGainFactor)
  ); // expected value: 3.981
  log.writeAll();
  std::exit(EXIT_SUCCESS);
}
