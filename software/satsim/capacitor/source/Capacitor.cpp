// Capacitor.cpp
// Capacitor class implementation file
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
#include <algorithm>         // max

// satsim
#include <Capacitor.hpp>     // Capacitor
#include <EnergyStorage.hpp> // EnergyStorage
#include <Logger.hpp>        // Logger

namespace satsim {
  Capacitor::Capacitor(
   const double& capacity_F, const double& esr_Ohm,
   const double& initialCharge_C, const double& initialCurrent_A, Logger* logger
  ) : EnergyStorage(initialCurrent_A, logger), simTime_sec(0.0) {
    this->capacity_F = std::max(0.0,capacity_F);
    this->esr_Ohm = std::max(0.0,esr_Ohm);
    this->charge_C = std::max(0.0,initialCharge_C);
  }

  Capacitor* Capacitor::clone() const {
    return new Capacitor(*this);
  }

  double Capacitor::getCapacity() const {
    return this->capacity_F;
  }

  double Capacitor::getEsr() const {
    return this->esr_Ohm;
  }

  double Capacitor::getCharge() const {
    return this->charge_C;
  }

  double Capacitor::getVoltage() const {
    return this->charge_C/this->capacity_F;
  }

  void Capacitor::update(const double& seconds) {
    double sanitizedSeconds = std::max(0.0,seconds);
    this->simTime_sec += sanitizedSeconds;
    double delta_C = this->getCurrent()*sanitizedSeconds;
    if(this->getCurrent()<0.0 && this->charge_C==0.0) {
      this->setCurrent((0.0-this->charge_C)/sanitizedSeconds);
      this->charge_C = 0.0;
    } else if(this->getCurrent()<0.0 && this->charge_C+delta_C<0.0) {
      this->setCurrent((0.0-this->charge_C)/sanitizedSeconds);
      this->charge_C = 0.0;
      this->logEvent("cap-depleted",this->simTime_sec);
    } else {
      this->charge_C += delta_C;
    }
  }
}
