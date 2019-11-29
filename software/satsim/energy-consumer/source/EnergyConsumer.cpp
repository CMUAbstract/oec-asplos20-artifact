// EnergyConsumer.cpp
// Energy consumer class implementation file
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
#include <algorithm>          // max
#include <string>             // string

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <Logger.hpp>         // Logger

namespace satsim {
  EnergyConsumer::EnergyConsumer(
   const double& initialVoltage_V, const double& initialPower_W, Logger* logger
  ) : logger(logger) {
    this->instantaneousVoltage_V = std::max(0.0,initialVoltage_V);
    if(this->instantaneousVoltage_V == 0.0) {
      this->setOff();
    } else {
      this->instantaneousPower_W = std::max(0.0,initialPower_W);
    }
  }

  EnergyConsumer* EnergyConsumer::clone() const {
    return new EnergyConsumer(*this);
  }

  double EnergyConsumer::getVoltage() const {
    return this->instantaneousVoltage_V;
  }

  double EnergyConsumer::getPower() const {
    return this->instantaneousPower_W;
  }

  double EnergyConsumer::getCurrent() const {
    if(this->instantaneousVoltage_V == 0.0) {
      return 0.0;
    } else {
      return this->instantaneousPower_W/this->instantaneousVoltage_V;
    }
  }

  void EnergyConsumer::setVoltage(const double& volts) {
    this->instantaneousVoltage_V = std::max(0.0,volts);
    if(this->instantaneousVoltage_V == 0.0) {
      this->setOff();
    }
  }

  void EnergyConsumer::setPower(const double& watts) {
    this->instantaneousPower_W = std::max(0.0,watts);
  }

  void EnergyConsumer::setOff() {
    this->instantaneousPower_W = 0.0;
  }

  void EnergyConsumer::logEvent(const std::string& name, const double& time) {
    if(this->logger!=NULL) {
      this->logger->logEvent(name, time);
    }
  }

  void EnergyConsumer::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->logger!=NULL) {
      this->logger->logMeasurement(name, time, measurement);
    }
  }

  void EnergyConsumer::update(const double& seconds) {}
}
