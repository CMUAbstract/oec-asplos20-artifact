// Orbit.cpp
// Orbit class implementation file
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
