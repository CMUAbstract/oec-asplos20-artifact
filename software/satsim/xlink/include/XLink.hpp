// XLink.hpp
// XLink class header file
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

#ifndef SATSIM_XLINK_HPP
#define SATSIM_XLINK_HPP

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <Logger.hpp>         // Logger

namespace satsim {
  class XLink: public EnergyConsumer {
  public:
    enum class PowerState: uint8_t {
      OFF  = 0,
      RX   = 1,
      RXTX = 2
    };
    XLink(
     const double& initialVoltage_V, const PowerState& initialPowerState,
     Logger* logger=NULL
    );
    XLink(const XLink& xlink) = default;
    XLink(XLink&& xlink) = default;
    virtual ~XLink() = default;
    virtual XLink& operator=(const XLink& xlink) = default;
    virtual XLink& operator=(XLink&& xlink) = default;
    virtual XLink* clone() const;
    virtual void update(const double& seconds);
  private:
    PowerState powerState;
    double simTime_sec;
    double getWatt(const PowerState& powerState) const;
  };
}

#endif
