// EnergyConsumer.cpp
// Energy consumer class implementation file
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
