// SimpleSolarCell.cpp
// Simple solar cell class implementation file
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
#include <algorithm>           // max
#include <string>              // to_string

// satsim
#include <EnergyHarvester.hpp> // EnergyHarvester
#include <Logger.hpp>          // Logger
#include <SimpleSolarCell.hpp> // SimpleSolarCell

namespace satsim {
  SimpleSolarCell::SimpleSolarCell(
   const double& vmp_V, const double& imp_A, const double& initialVoltage_V,
   Logger* logger
  ) : EnergyHarvester(initialVoltage_V, imp_A, logger), vmp_V(vmp_V),
      imp_A(imp_A), simTime_sec(0.0) {
    updateInstantaneousCurrent();
  }

  SimpleSolarCell* SimpleSolarCell::clone() const {
    return new SimpleSolarCell(*this);
  }

  void SimpleSolarCell::update(const double& seconds) {
    double sanitizedSeconds = std::max(0.0,seconds);
    this->simTime_sec += sanitizedSeconds;
    updateInstantaneousCurrent();
  }

  void SimpleSolarCell::updateInstantaneousCurrent() {
    if(this->vmp_V<=this->getVoltage() && this->getCurrent()!=0.0) {
      this->setCurrent(0.0);
      //this->logEvent(
      // "ssc-"+std::to_string(this->getWorkerId())+"-current-shutoff",
      // this->simTime_sec
      //);
    } else if(
       this->getVoltage()<this->vmp_V && this->getCurrent()!=this->imp_A
      ) {
      this->setCurrent(this->imp_A);
    }
  }
}
