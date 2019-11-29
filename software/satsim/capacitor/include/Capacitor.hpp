// Capacitor.hpp
// Capacitor class header file
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

#ifndef SATSIM_CAPACITOR_HPP
#define SATSIM_CAPACITOR_HPP

// satsim
#include <EnergyStorage.hpp> // EnergyHarvester
#include <Logger.hpp>        // Logger

namespace satsim {
  class Capacitor: public EnergyStorage {
  public:
    Capacitor(
     const double& capacity_F, const double& esr_Ohm,
     const double& initialCharge_C, const double& initialCurrent_A,
     Logger* logger=NULL
    );
    Capacitor(const Capacitor& capacitor) = default;
    Capacitor(Capacitor&& capacitor) = default;
    virtual ~Capacitor() = default;
    virtual Capacitor& operator=(const Capacitor& capacitor) = default;
    virtual Capacitor& operator=(Capacitor&& capacitor) = default;
    virtual Capacitor* clone() const;
    double getCapacity() const;
    double getEsr() const;
    double getCharge() const;
    double getVoltage() const;
    virtual void update(const double& seconds);
  private:
    double capacity_F;
    double esr_Ohm;
    double charge_C;
    double simTime_sec;
  };
}

#endif
