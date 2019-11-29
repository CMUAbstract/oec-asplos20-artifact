// EnergyStorage.cpp
// Energy storage class implementation file
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
