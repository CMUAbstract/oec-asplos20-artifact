// EHSatellite.cpp
// EHSatellite class implementation file
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
#include <algorithm>       // max
#include <string>          // string

// satsim
#include <EHSatellite.hpp> // EHSatellite
#include <Logger.hpp>      // Logger
#include <Orbit.hpp>       // Orbit

namespace satsim {
  EHSatellite::EHSatellite(
   const Orbit& orbit, const EHSystem& ehsystem, Logger* logger
  ) : Satellite(orbit,logger), ehsystem(ehsystem) {}

  EHSatellite* EHSatellite::clone() const {
    return new EHSatellite(*this);
  }

  EHSystem EHSatellite::getEHSystem() const {
    return this->ehsystem;
  }

  // Send the actual pointers to allow for energy consumer state updates
  std::vector<EnergyConsumer*> EHSatellite::getEnergyConsumers() {
    return this->ehsystem.getEnergyConsumers();
  }

  void EHSatellite::update(const double& seconds) {
    double sanitizedSeconds = std::max(0.0,seconds);
    this->Satellite::update(sanitizedSeconds);
    this->ehsystem.update(sanitizedSeconds);
  }
}
