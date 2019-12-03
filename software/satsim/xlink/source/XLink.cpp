// XLink.cpp
// XLink class implementation file
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
#include <Logger.hpp>         // Logger
#include <XLink.hpp>          // XLink

namespace satsim {
  XLink::XLink(
   const double& initialVoltage_V, const PowerState& initialPowerState,
   Logger* logger
  ) : EnergyConsumer(initialVoltage_V, 0.0, logger),
      powerState(initialPowerState), simTime_sec(0.0) {
    this->setPower(getWatt(this->powerState));
  }

  XLink* XLink::clone() const {
    return new XLink(*this);
  }

  void XLink::update(const double& seconds) {
    double sanitizedSeconds = std::max(0.0,seconds);
    this->simTime_sec += sanitizedSeconds;
    if(this->powerState!=XLink::PowerState::OFF && this->getVoltage()<5.0) {
      this->logEvent("xlink-blackout",this->simTime_sec);
      this->powerState = XLink::PowerState::OFF;
      this->setPower(getWatt(this->powerState));
    }
  }

  double XLink::getWatt(const XLink::PowerState& powerState) const {
    double watt = 0.0;
    switch(powerState) {
      case XLink::PowerState::OFF:
        watt = 0.0;
        break;
      case XLink::PowerState::RX:
        watt = 5.0;
        break;
      case XLink::PowerState::RXTX:
        watt = 15.0;
        break;
      default:
        watt = 0.0;
        break;
    }
    return watt;
  }
}
