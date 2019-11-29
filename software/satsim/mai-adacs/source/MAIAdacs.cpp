// MAIAdacs.cpp
// MAI ADACS class implementation file
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
