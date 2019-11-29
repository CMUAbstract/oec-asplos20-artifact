// EnergyHarvester.hpp
// Energy harvester class header file
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
