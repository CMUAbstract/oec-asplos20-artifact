// Satellite.cpp
// Satellite class implementation file
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
#include <algorithm>     // max
#include <string>        // string

// satsim
#include <Logger.hpp>    // Logger
#include <Orbit.hpp>     // Orbit
#include <Satellite.hpp> // Satellite

namespace satsim {
  Satellite::Satellite(const Orbit& orbit, Logger* logger) :
   orbit(orbit), logger(logger) {}

  Satellite* Satellite::clone() const {
    return new Satellite(*this);
  }

  Orbit Satellite::getOrbit() const {
    return this->orbit;
  }

  Orbit* Satellite::getOrbitPtr() {
    return &(this->orbit);
  }

  void Satellite::logEvent(const std::string& name, const double& time) {
    if(this->logger!=NULL) {
      this->logger->logEvent(name, time);
    }
  }

  void Satellite::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->logger!=NULL) {
      this->logger->logMeasurement(name, time, measurement);
    }
  }

  void Satellite::update(const double& seconds) {
    double sanitizedSeconds = std::max(0.0,seconds);
    this->orbit.update(sanitizedSeconds);
  }
}
