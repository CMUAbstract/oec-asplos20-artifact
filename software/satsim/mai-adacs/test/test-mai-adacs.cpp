// test-mai-adacs.cpp
// MAI ADACS class test file
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
#include <cstddef>      // size_t

// satsim
#include <MAIAdacs.hpp> // MAIAdacs
#include <Logger.hpp>   // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::MAIAdacs maiadacs(7.0, satsim::MAIAdacs::PowerState::NADIR, &logger);
  satsim::MAIAdacs* maClone = maiadacs.clone();
  delete maClone;
  // Each iteration is 0.1 s
  for(size_t i=0; i<1200; i++) {
    if(i%10==0) {
      maiadacs.logMeasurement(
       "voltage-v",static_cast<double>(i)/10.0,maiadacs.getVoltage()
      );
      maiadacs.logMeasurement(
       "current-a",static_cast<double>(i)/10.0,maiadacs.getCurrent()
      );
    }
    if(i%600==0) {
      maiadacs.logEvent("minute",static_cast<double>(i)/10.0);
    }
    maiadacs.setVoltage(maiadacs.getVoltage()-0.002);
    maiadacs.update(0.1);
  }
  logger.exportCsvs("../test");
  return 0;
}
