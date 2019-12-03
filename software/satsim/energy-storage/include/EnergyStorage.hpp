// EnergyStorage.hpp
// Energy storage class header file
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

#ifndef SATSIM_ENERGY_STORAGE_HPP
#define SATSIM_ENERGY_STORAGE_HPP

// Standard library
#include <string>     // string

// satsim
#include <ILog.hpp>   // Logger interface
#include <ISim.hpp>   // Simulator interface
#include <Logger.hpp> // Logger

namespace satsim {
  class EnergyStorage: public ILog, public ISim {
  public:
    EnergyStorage(const double& initialCurrent_A, Logger* logger=NULL);
    EnergyStorage(const EnergyStorage& energyStorage) = default;
    EnergyStorage(EnergyStorage&& energyStorage) = default;
    virtual ~EnergyStorage() = default;
    virtual EnergyStorage& operator=(const EnergyStorage& energyStorage) = default;
    virtual EnergyStorage& operator=(EnergyStorage&& energyStorage) = default;
    virtual EnergyStorage* clone() const;
    double getCurrent() const;
    void setCurrent(const double& amperes);
    virtual void logEvent(const std::string& name, const double& time);
    virtual void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    virtual void update(const double& seconds);
  private:
    double instantaneousCurrent_A; // current at present time in Amperes
    Logger* logger;                // singleton, should not be deleted
  };
}

#endif
