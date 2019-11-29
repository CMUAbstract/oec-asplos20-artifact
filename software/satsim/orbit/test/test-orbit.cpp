// test-orbit.cpp
// Orbit class test file
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
#include <Logger.hpp> // Logger
#include <Orbit.hpp>  // Orbit

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::Orbit orbit(5580.0, 0.0, &logger);
  double period_sec = orbit.getPeriod();
  double posn_rad = orbit.getPosn();
  // Each iteration is 1 s
  double prev_posn_rad = satsim::Orbit::TAU;
  for(size_t i=0; i<16740; i++) {
    if(i%60==0) {
      orbit.logEvent("minute",static_cast<double>(i));
    }
    if(i%120==0) {
      orbit.logMeasurement("posn-rad",static_cast<double>(i),orbit.getPosn());
    }
    if(orbit.getPosn() < prev_posn_rad) {
      orbit.logEvent("orbit-period",static_cast<double>(i));
    }
    prev_posn_rad = orbit.getPosn();
    orbit.update(1.0);
  }
  logger.exportCsvs("../test");
  return 0;
}
