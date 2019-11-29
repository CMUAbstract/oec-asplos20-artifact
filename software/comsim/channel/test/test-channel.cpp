// test-channel.cpp
// Channel class test file
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
