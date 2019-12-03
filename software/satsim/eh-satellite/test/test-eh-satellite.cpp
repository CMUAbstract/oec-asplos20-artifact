// test-eh-satellite.cpp
// EHSatellite class test file
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
#include <cstddef>             // size_t

// satsim
#include <Capacitor.hpp>       // Capacitor
#include <EHSatellite.hpp>     // EHSatellite
#include <EHSystem.hpp>        // EHSystem
#include <EnergyConsumer.hpp>  // EnergyConsumer
#include <EnergyHarvester.hpp> // EnergyHarvester
#include <JetsonTX2.hpp>       // JetsonTX2
#include <Logger.hpp>          // Logger
#include <Orbit.hpp>           // Orbit
#include <Satellite.hpp>       // Satellite
#include <SimpleSolarCell.hpp> // SimpleSolarCell

int main(int argc, char** argv) {
  satsim::Logger logger("s");
  satsim::Orbit orbit(5580.0, 0.0);
  satsim::EnergyHarvester* simpleSolarCell =
   new satsim::SimpleSolarCell(7.029, 1.0034, 5.75, &logger);
  satsim::Capacitor capacitor(5.0, 0.168, 28.75, 1.0034, &logger);
  satsim::EHSystem ehsystem(*simpleSolarCell, capacitor, &logger);
  delete simpleSolarCell;
  satsim::JetsonTX2 jetsonTX2(
   5.75, satsim::JetsonTX2::PowerState::SLEEP, 3072, &logger
  );
  ehsystem.addEnergyConsumer(jetsonTX2);
  satsim::EHSatellite ehsatellite(orbit, ehsystem, &logger);
  // Each iteration is 1.0e-6 s
  for(size_t i=0; i<10000000; i++) {
    if(i%10000==0) {
      ehsatellite.logMeasurement(
       "cap-V", ehsatellite.getEHSystem().getSimTime(),
       ehsatellite.getEHSystem().getCapacitor().getVoltage()
      );
    }
    if(i%1000000==0) {
      ehsatellite.logEvent("second",ehsatellite.getEHSystem().getSimTime());
    }
    ehsatellite.update(1.0e-6);
  }
  logger.exportCsvs("../test");
  return 0;
}
