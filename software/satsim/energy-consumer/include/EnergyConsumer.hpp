// EnergyConsumer.hpp
// Energy consumer class header file
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

#ifndef SATSIM_ENERGY_CONSUMER_HPP
#define SATSIM_ENERGY_CONSUMER_HPP

// Standard library
#include <string>     // string

// satsim
#include <ILog.hpp>   // Logger interface
#include <ISim.hpp>   // Simulator interface
#include <Logger.hpp> // Logger

namespace satsim {
  class EnergyConsumer: public ILog, public ISim {
  public:
    EnergyConsumer(
     const double& initialVoltage_V, const double& initialPower_W,
     Logger* logger=NULL
    );
    EnergyConsumer(const EnergyConsumer& energyConsumer) = default;
    EnergyConsumer(EnergyConsumer&& energyConsumer) = default;
    virtual ~EnergyConsumer() = default;
    virtual EnergyConsumer& operator=(const EnergyConsumer& energyConsumer) = default;
    virtual EnergyConsumer& operator=(EnergyConsumer&& energyConsumer) = default;
    virtual EnergyConsumer* clone() const;
    double getVoltage() const;
    double getPower() const;
    double getCurrent() const;
    void setVoltage(const double& volts);
    void setPower(const double& watts);
    void setOff();
    virtual void logEvent(const std::string& name, const double& time);
    virtual void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    virtual void update(const double& seconds);
  private:
    double instantaneousVoltage_V; // voltage at present time in Volts
    double instantaneousPower_W;   // power at present time in Watts
    Logger* logger;                // singleton, should not be deleted
  };
}

#endif
