// test-receive.cpp
// Receive class test file
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
#include <cstdlib>      // exit, EXIT_SUCCESS
#include <iostream>     // cout
#include <ostream>      // endl

// comsim
#include <DateTime.hpp> // DateTime
#include <Log.hpp>      // Log
#include <LogLevel.hpp> // LogLevel
#include <Receive.hpp>  // Receive

int main(int argc, char** argv) {
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::TRACE};
  comsim::Log log(levels,"../test");
  comsim::DateTime dateTime(1995,11,18,12,46, 0,0);
  std::array<double,3> posn = {-4400.594, 1932.870, 4760.712};
  comsim::Receive receive(posn, 6.0, &dateTime, 1, &log);
  log.evnt(comsim::LogLevel::TRACE, "Constructor", "test-success");
  std::array<double,3> testPosn = receive.getPosn();
  log.evnt(comsim::LogLevel::TRACE, "getPosn", "test-success");
  double testGainFactor = receive.getGain();
  log.meas(
   comsim::LogLevel::TRACE, dateTime.toString(), "gain",
   std::to_string(testGainFactor)
  ); // expected value: 3.981
  log.writeAll();
  std::exit(EXIT_SUCCESS);
}
