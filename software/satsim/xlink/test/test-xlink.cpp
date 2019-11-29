// test-xlink.cpp
// XLink class test file
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
#include <XLink.hpp>  // XLink
#include <Logger.hpp> // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::XLink xlink(7.0, satsim::XLink::PowerState::RXTX, &logger);
  satsim::XLink* xClone = xlink.clone();
  delete xClone;
  // Each iteration is 0.1 s
  for(size_t i=0; i<1200; i++) {
    if(i%10==0) {
      xlink.logMeasurement(
       "voltage-v",static_cast<double>(i)/10.0,xlink.getVoltage()
      );
      xlink.logMeasurement(
       "current-a",static_cast<double>(i)/10.0,xlink.getCurrent()
      );
    }
    if(i%600==0) {
      xlink.logEvent("minute",static_cast<double>(i)/10.0);
    }
    xlink.setVoltage(xlink.getVoltage()-0.002);
    xlink.update(0.1);
  }
  logger.exportCsvs("../test");
  return 0;
}
