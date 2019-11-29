// test-logger.cpp
// Logger class test file
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

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  // Each iteration is 1 ms
  for(size_t i=0; i<5000; i++) {
    if(i%100==0) {
      logger.logMeasurement(
       "voltage-V", 0.001*static_cast<double>(i), 0.0024*static_cast<double>(i)
      );
      logger.logMeasurement(
       "current-A", 0.001*static_cast<double>(i), 0.00002*static_cast<double>(i)
      );
    }
    if(i%1000==0) {
      logger.logEvent("second",0.001*static_cast<double>(i));
    }
  }
  logger.exportCsvs("../test");
  return 0;
}
