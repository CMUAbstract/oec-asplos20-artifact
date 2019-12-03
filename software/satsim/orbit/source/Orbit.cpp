// Orbit.cpp
// Orbit class implementation file
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
#include <algorithm>  // min, max
#include <string>     // string

// satsim
#include <Logger.hpp> // Logger
#include <Orbit.hpp>  // Orbit

namespace satsim {
  const double Orbit::TAU = 2.0*3.14159265358979323846;

  Orbit::Orbit(
   const double& period_sec, const double& posn_rad, Logger* logger
  ) {
    this->period_sec = std::max(5060.0,std::min(period_sec,2592000.0));
    this->posn_rad = std::max(0.0,std::min(posn_rad,TAU));
    if(this->posn_rad==TAU) {
      this->posn_rad = 0.0;
    }
    this->logger = logger;
  }

  double Orbit::getPeriod() const {
    return this->period_sec;
  }

  double Orbit::getPosn() const {
    return this->posn_rad;
  }

  void Orbit::logEvent(const std::string& name, const double& time) {
    if(this->logger!=NULL) {
      this->logger->logEvent(name, time);
    }
  }

  void Orbit::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->logger!=NULL) {
      this->logger->logMeasurement(name, time, measurement);
    }
  }

  void Orbit::update(const double& seconds) {
    double sanitizedSeconds = std::max(0.0,seconds);
    this->posn_rad += TAU*sanitizedSeconds/this->period_sec;
    while(this->posn_rad >= TAU) {
      this->posn_rad -= TAU;
    }
  }
}
