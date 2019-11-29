// EnergyConsumer.hpp
// Energy consumer class header file
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
