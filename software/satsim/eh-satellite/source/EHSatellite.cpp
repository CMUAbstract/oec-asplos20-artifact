// EHSatellite.cpp
// EHSatellite class implementation file
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
