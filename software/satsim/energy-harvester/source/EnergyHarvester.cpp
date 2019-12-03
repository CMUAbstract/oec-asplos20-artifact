// EnergyHarvester.cpp
// Energy harvester class implementation file
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
#include <algorithm>           // max
#include <string>              // string

// satsim
#include <EnergyHarvester.hpp> // EnergyHarvester
#include <Logger.hpp>          // Logger

namespace satsim {
  EnergyHarvester::EnergyHarvester(
   const double& initialVoltage_V, const double& initialCurrent_A,
   Logger* logger
  ) : workerId(0), logger(logger) {
    this->instantaneousVoltage_V = std::max(0.0,initialVoltage_V);
    this->instantaneousCurrent_A = std::max(0.0,initialCurrent_A);
  }

  EnergyHarvester* EnergyHarvester::clone() const {
    return new EnergyHarvester(*this);
  }

  size_t EnergyHarvester::getWorkerId() const {
    return this->workerId;
  }

  void EnergyHarvester::setWorkerId(const size_t& id) {
    this->workerId = id;
  }

  double EnergyHarvester::getVoltage() const {
    return this->instantaneousVoltage_V;
  }

  double EnergyHarvester::getCurrent() const {
    return this->instantaneousCurrent_A;
  }

  void EnergyHarvester::setVoltage(const double& volts) {
    this->instantaneousVoltage_V = std::max(0.0,volts);
  }

  void EnergyHarvester::setCurrent(const double& amperes) {
    this->instantaneousCurrent_A = std::max(0.0,amperes);
  }

  void EnergyHarvester::logEvent(const std::string& name, const double& time) {
    if(this->logger!=NULL) {
      this->logger->logEvent(name, time);
    }
  }

  void EnergyHarvester::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->logger!=NULL) {
      this->logger->logMeasurement(name, time, measurement);
    }
  }

  void EnergyHarvester::update(const double& seconds) {}
}
