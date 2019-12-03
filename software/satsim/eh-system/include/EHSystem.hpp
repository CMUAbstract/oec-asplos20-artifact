// EHSystem.hpp
// Energy harvesting system class header file
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

#ifndef SATSIM_EH_SYSTEM_HPP
#define SATSIM_EH_SYSTEM_HPP

// Standard library
#include <string>              // string
#include <vector>              // vector

// satsim
#include <Capacitor.hpp>       // Capacitor
#include <EnergyConsumer.hpp>  // EnergyConsumer
#include <EnergyHarvester.hpp> // EnergyHarvester
#include <ILog.hpp>            // Logger interface
#include <ISim.hpp>            // Simulator interface
#include <Logger.hpp>          // Logger

namespace satsim {
  class EHSystem : public ILog, public ISim {
  public:
    EHSystem(
     const EnergyHarvester& energyHarvester, const Capacitor& capacitor,
     Logger* logger=NULL
    );
    EHSystem(const EHSystem& ehsystem); // Needs all 5 b/c custom destructor
    EHSystem(EHSystem&& ehsystem);
    virtual ~EHSystem();
    virtual EHSystem& operator=(const EHSystem& ehsystem);
    virtual EHSystem& operator=(EHSystem&& ehsystem);
    EnergyHarvester* getEnergyHarvester() const;
    Capacitor getCapacitor() const;
    std::vector<const EnergyConsumer*> getEnergyConsumers() const;
    double getTotalPower() const;
    double getNodeVoltage() const;
    double getSimTime() const;
    std::vector<EnergyConsumer*> getEnergyConsumers(); // non-const for state updates
    Logger* getLogger() const;
    void addEnergyConsumer(const EnergyConsumer& energyConsumer);
    void logEvent(const std::string& name, const double& time);
    void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    void update(const double& seconds);
  private:
    EnergyHarvester* energyHarvester;
    Capacitor capacitor;
    std::vector<EnergyConsumer*> energyConsumers;
    double totalPower_W;  // Total power consumed by all devices in Watts
    double nodeVoltage_V; // Voltage at the device node in Volts
    double simTime_sec;   // Energy harvesting system time in seconds
    Logger* logger;       // singleton, should not be deleted
    double calculateDiscriminant() const;
    double calculateNodeVoltage() const;
    void updateTotalPower();
    void updateNodeVoltage();
  };
}

#endif
