// MAIAdacs.cpp
// MAI ADACS class implementation file
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
#include <algorithm>          // max

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <MAIAdacs.hpp>       // MAIAdacs
#include <Logger.hpp>         // Logger

namespace satsim {
  MAIAdacs::MAIAdacs(
   const double& initialVoltage_V, const PowerState& initialPowerState,
   Logger* logger
  ) : EnergyConsumer(initialVoltage_V, 0.0, logger),
      powerState(initialPowerState), simTime_sec(0.0) {
    this->setPower(getWatt(this->powerState));
  }

  MAIAdacs* MAIAdacs::clone() const {
    return new MAIAdacs(*this);
  }

  void MAIAdacs::update(const double& seconds) {
    double sanitizedSeconds = std::max(0.0,seconds);
    this->simTime_sec += sanitizedSeconds;
    if(this->powerState!=MAIAdacs::PowerState::OFF && this->getVoltage()<5.0) {
      this->logEvent("mai-adacs-blackout",this->simTime_sec);
      this->powerState = MAIAdacs::PowerState::OFF;
      this->setPower(getWatt(this->powerState));
    }
  }

  double MAIAdacs::getWatt(const MAIAdacs::PowerState& powerState) const {
    double watt = 0.0;
    switch(powerState) {
      case MAIAdacs::PowerState::OFF:
        watt = 0.0;
        break;
      case MAIAdacs::PowerState::NADIR:
        watt = 1.13;
        break;
      default:
        watt = 0.0;
        break;
    }
    return watt;
  }
}
