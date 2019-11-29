// EHSatellite.hpp
// EHSatellite class header file
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

#ifndef SATSIM_EH_SATELLITE_HPP
#define SATSIM_EH_SATELLITE_HPP

// Standard library
#include <string>        // string

// satsim
#include <EHSystem.hpp>  // EHSystem
#include <ILog.hpp>      // Logger interface
#include <ISim.hpp>      // Simulator interface
#include <Logger.hpp>    // Logger
#include <Orbit.hpp>     // Orbit
#include <Satellite.hpp> // Satellite

namespace satsim {
  class EHSatellite: public Satellite {
  public:
    EHSatellite(
     const Orbit& orbit, const EHSystem& ehsystem, Logger* logger=NULL
    );
    EHSatellite(const EHSatellite& ehsatellite) = default;
    EHSatellite(EHSatellite&& ehsatellite) = default;
    virtual ~EHSatellite() = default;
    virtual EHSatellite& operator=(const EHSatellite& ehsatellite) = default;
    virtual EHSatellite& operator=(EHSatellite&& ehsatellite) = default;
    virtual EHSatellite* clone() const;
    EHSystem getEHSystem() const;
    std::vector<EnergyConsumer*> getEnergyConsumers(); // non-const for state updates
    virtual void update(const double& seconds);
  private:
    EHSystem ehsystem;
    Logger* logger;    // singleton, should not be deleted
  };
}

#endif
