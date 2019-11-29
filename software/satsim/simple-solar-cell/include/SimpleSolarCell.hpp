// SimpleSolarCell.hpp
// Simple solar cell class header file
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
