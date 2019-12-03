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
#include <cstddef>       // size_t

// satsim
#include <Logger.hpp>    // Logger
#include <Orbit.hpp>     // Orbit
#include <Satellite.hpp> // Satellite

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::Satellite satellite(satsim::Orbit(5580.0, 0.0), &logger);
  satsim::Orbit orbit = satellite.getOrbit();
  // Each iteration is 1 s
  double prev_posn_rad = satsim::Orbit::TAU;
  for(size_t i=0; i<16740; i++) {
    if(i%60==0) {
      satellite.logEvent("minute",static_cast<double>(i));
    }
    if(i%120==0) {
      satellite.logMeasurement(
       "posn-rad",static_cast<double>(i),satellite.getOrbit().getPosn()
      );
    }
    if(satellite.getOrbit().getPosn() < prev_posn_rad) {
      satellite.logEvent("orbit period",static_cast<double>(i));
    }
    prev_posn_rad = satellite.getOrbit().getPosn();
    satellite.update(1.0);
  }
  logger.exportCsvs("../test");
  return 0;
}
