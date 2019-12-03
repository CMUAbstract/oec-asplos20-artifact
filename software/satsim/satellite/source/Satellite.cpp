// Satellite.cpp
// Satellite class implementation file
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
