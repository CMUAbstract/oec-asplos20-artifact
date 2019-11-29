// test-eh-system.cpp
// Energy harvesting system class test file
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
#include <Capacitor.hpp>       // Capacitor
#include <EHSystem.hpp>        // EnergyConsumer
#include <EnergyConsumer.hpp>  // EnergyConsumer
#include <EnergyHarvester.hpp> // EnergyHarvester
#include <JetsonTX2.hpp>       // JetsonTX2
#include <Logger.hpp>          // Logger
#include <SimpleSolarCell.hpp> // SimpleSolarCell

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::EnergyHarvester* simpleSolarCell =
   new satsim::SimpleSolarCell(7.029, 1.0034, 5.75, &logger);
  satsim::Capacitor capacitor(5.0, 0.168, 28.75, 1.0034, &logger);
  satsim::EHSystem ehsystem(*simpleSolarCell, capacitor, &logger);
  delete simpleSolarCell;
  satsim::JetsonTX2 jetsonTX2(
   5.75, satsim::JetsonTX2::PowerState::SLEEP, 3072, &logger
  );
  ehsystem.addEnergyConsumer(jetsonTX2);
  // Each iteration is 1.0e-6 s
  for(size_t i=0; i<10000000; i++) {
    if(i%10000==0) {
      ehsystem.logMeasurement(
       "cap-V",ehsystem.getSimTime(),ehsystem.getCapacitor().getVoltage()
      );
    }
    if(i%1000000==0) {
      ehsystem.logEvent("second",ehsystem.getSimTime());
    }
    ehsystem.update(1.0e-6);
  }
  logger.exportCsvs("../test");
  return 0;
}
