// MAIAdacs.hpp
// MAI ADACS class header file
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
