// EnergyHarvester.hpp
// Energy harvester class header file
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

#ifndef SATSIM_ENERGY_HARVESTER_HPP
#define SATSIM_ENERGY_HARVESTER_HPP

// Standard library
#include <string>     // string

// satsim
#include <ILog.hpp>   // Logger interface
#include <ISim.hpp>   // Simulator interface
#include <Logger.hpp> // Logger

namespace satsim {
  class EnergyHarvester: public ILog, public ISim {
  public:
    EnergyHarvester(
     const double& initialVoltage_V, const double& initialCurrent_A,
     Logger* logger=NULL
    );
    EnergyHarvester(const EnergyHarvester& energyHarvester) = default;
    EnergyHarvester(EnergyHarvester&& energyHarvester) = default;
    virtual ~EnergyHarvester() = default;
    virtual EnergyHarvester& operator=(const EnergyHarvester& energyHarvester) = default;
    virtual EnergyHarvester& operator=(EnergyHarvester&& energyHarvester) = default;
    virtual EnergyHarvester* clone() const;
    size_t getWorkerId() const;
    void setWorkerId(const size_t& id);
    double getVoltage() const;
    double getCurrent() const;
    void setVoltage(const double& volts);
    void setCurrent(const double& amperes);
    virtual void logEvent(const std::string& name, const double& time);
    virtual void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    virtual void update(const double& seconds);
  private:
    double instantaneousVoltage_V; // voltage at present time in Volts
    double instantaneousCurrent_A; // current at present time in Amperes
    size_t workerId;
    Logger* logger;                // singleton, should not be deleted
  };
}

#endif
