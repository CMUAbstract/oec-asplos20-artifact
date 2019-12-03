// Capacitor.cpp
// Capacitor class implementation file
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
