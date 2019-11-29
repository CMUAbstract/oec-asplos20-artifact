// test-energy-storage.cpp
// Energy storage class test file
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
#include <cstddef>           // size_t

// satsim
#include <EnergyStorage.hpp> // EnergyStorage
#include <Logger.hpp>        // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::EnergyStorage energyStorage(1.0034, &logger);
  satsim::EnergyStorage* esClone = energyStorage.clone();
  delete esClone;
  // Each iteration is 0.1 s
  for(size_t i=0; i<1200; i++) {
    if(i%10==0) {
      energyStorage.logMeasurement(
       "current-a",static_cast<double>(i)/10.0,energyStorage.getCurrent()
      );
    }
    if(i%600==0) {
      energyStorage.logEvent("minute",static_cast<double>(i)/10.0);
    }
    energyStorage.update(0.1);
  }
  logger.exportCsvs("../test");
  return 0;
}
