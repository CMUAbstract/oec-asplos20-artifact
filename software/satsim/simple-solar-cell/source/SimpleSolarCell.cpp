// SimpleSolarCell.cpp
// Simple solar cell class implementation file
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
