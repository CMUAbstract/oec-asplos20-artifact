// XLink.cpp
// XLink class implementation file
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
