// test-energy-consumer.cpp
// Energy consumer class test file
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
#include <cstddef>            // size_t

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <Logger.hpp>         // Logger

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::EnergyConsumer energyConsumer(6.5, 11.3272, &logger);
  satsim::EnergyConsumer* ecClone = energyConsumer.clone();
  delete ecClone;
  // Each iteration is 0.1 s
  for(size_t i=0; i<1200; i++) {
    if(i%10==0) {
      energyConsumer.logMeasurement(
       "power-w",static_cast<double>(i)/10.0,energyConsumer.getPower()
      );
    }
    if(i%600==0) {
      energyConsumer.logEvent("minute",static_cast<double>(i)/10.0);
    }
    energyConsumer.update(0.1);
  }
  logger.exportCsvs("../test");
  return 0;
}
