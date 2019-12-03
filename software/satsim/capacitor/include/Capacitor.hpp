// Capacitor.hpp
// Capacitor class header file
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
