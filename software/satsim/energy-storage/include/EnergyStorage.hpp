// EnergyStorage.hpp
// Energy storage class header file
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
