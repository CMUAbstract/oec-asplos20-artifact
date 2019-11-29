// EHSystem.hpp
// Energy harvesting system class header file
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
