// EnergyStorage.cpp
// Energy storage class implementation file
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
#include <string>            // string

// satsim
#include <EnergyStorage.hpp> // EnergyStorage
#include <Logger.hpp>        // Logger

namespace satsim {
  EnergyStorage::EnergyStorage(const double& initialCurrent_A, Logger* logger) :
   instantaneousCurrent_A(initialCurrent_A), logger(logger) {}

  EnergyStorage* EnergyStorage::clone() const {
    return new EnergyStorage(*this);
  }

  double EnergyStorage::getCurrent() const {
    return this->instantaneousCurrent_A;
  }

  void EnergyStorage::setCurrent(const double& amperes) {
    this->instantaneousCurrent_A = amperes;
  }

  void EnergyStorage::logEvent(const std::string& name, const double& time) {
    if(this->logger!=NULL) {
      this->logger->logEvent(name, time);
    }
  }

  void EnergyStorage::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->logger!=NULL) {
      this->logger->logMeasurement(name, time, measurement);
    }
  }

  void EnergyStorage::update(const double& seconds) {}
}
