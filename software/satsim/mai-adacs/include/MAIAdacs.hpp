// MAIAdacs.hpp
// MAI ADACS class header file
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

#ifndef SATSIM_MAI_ADACS_HPP
#define SATSIM_MAI_ADACS_HPP

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <Logger.hpp>         // Logger

namespace satsim {
  class MAIAdacs: public EnergyConsumer {
  public:
    enum class PowerState: uint8_t {
      OFF    = 0,
      NADIR  = 1
    };
    MAIAdacs(
     const double& initialVoltage_V, const PowerState& initialPowerState,
     Logger* logger=NULL
    );
    MAIAdacs(const MAIAdacs& maiadacs) = default;
    MAIAdacs(MAIAdacs&& maiadacs) = default;
    virtual ~MAIAdacs() = default;
    virtual MAIAdacs& operator=(const MAIAdacs& maiadacs) = default;
    virtual MAIAdacs& operator=(MAIAdacs&& maiadacs) = default;
    virtual MAIAdacs* clone() const;
    virtual void update(const double& seconds);
  private:
    PowerState powerState;
    double simTime_sec;
    double getWatt(const PowerState& powerState) const;
  };
}

#endif
