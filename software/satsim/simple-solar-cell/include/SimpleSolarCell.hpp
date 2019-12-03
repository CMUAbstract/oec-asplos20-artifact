// SimpleSolarCell.hpp
// Simple solar cell class header file
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

#ifndef SATSIM_SIMPLE_SOLAR_CELL_HPP
#define SATSIM_SIMPLE_SOLAR_CELL_HPP

// satsim
#include <EnergyHarvester.hpp> // EnergyHarvester
#include <Logger.hpp>          // Logger

namespace satsim {
  class SimpleSolarCell: public EnergyHarvester {
  public:
    SimpleSolarCell(
     const double& vmp_V, const double& imp_A, const double& initialVoltage_V,
     Logger* logger=NULL
    );
    SimpleSolarCell(const SimpleSolarCell& simpleSolarCell) = default;
    SimpleSolarCell(SimpleSolarCell&& simpleSolarCell) = default;
    virtual ~SimpleSolarCell() = default;
    virtual SimpleSolarCell& operator=(const SimpleSolarCell& simpleSolarCell) = default;
    virtual SimpleSolarCell& operator=(SimpleSolarCell&& simpleSolarCell) = default;
    virtual SimpleSolarCell* clone() const;
    virtual void update(const double& seconds);
  private:
    double vmp_V;
    double imp_A;
    double simTime_sec;
    void updateInstantaneousCurrent();
  };
}

#endif
