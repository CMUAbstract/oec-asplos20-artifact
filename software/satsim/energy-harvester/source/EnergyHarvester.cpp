// EnergyHarvester.cpp
// Energy harvester class implementation file
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
