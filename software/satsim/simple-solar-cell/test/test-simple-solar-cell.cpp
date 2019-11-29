// test-simple-solar-cell.cpp
// Simple solar cell class test file
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
#include <cstddef>             // size_t

// satsim
#include <Logger.hpp>          // Logger
#include <SimpleSolarCell.hpp> // SimpleSolarCell

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::SimpleSolarCell simpleSolarCell(7.029, 1.0034, 6.5, &logger);
  satsim::SimpleSolarCell* sscClone = simpleSolarCell.clone();
  delete sscClone;
  // Each iteration is 0.1 s
  for(size_t i=0; i<1200; i++) {
    if(i%10==0) {
      simpleSolarCell.logMeasurement(
       "voltage-v",static_cast<double>(i)/10.0,simpleSolarCell.getVoltage()
      );
      simpleSolarCell.logMeasurement(
       "current-a",static_cast<double>(i)/10.0,simpleSolarCell.getCurrent()
      );
    }
    if(i%600==0) {
      simpleSolarCell.logEvent("minute",static_cast<double>(i)/10.0);
    }
    simpleSolarCell.setVoltage(simpleSolarCell.getVoltage()+0.001);
    simpleSolarCell.update(0.1);
  }
  logger.exportCsvs("../test");
  return 0;
}
