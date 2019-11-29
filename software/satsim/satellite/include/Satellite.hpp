// Satellite.hpp
// Satellite class header file
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

#ifndef SATSIM_SATELLITE_HPP
#define SATSIM_SATELLITE_HPP

// Standard library
#include <string>     // string

// satsim
#include <ILog.hpp>   // Logger interface
#include <ISim.hpp>   // Simulator interface
#include <Logger.hpp> // Logger
#include <Orbit.hpp>  // Orbit

namespace satsim {
  class Satellite: public ILog, public ISim {
  public:
    Satellite(const Orbit& orbit, Logger* logger=NULL);
    Satellite(const Satellite& satellite) = default;
    Satellite(Satellite&& satellite) = default;
    virtual ~Satellite() = default;
    virtual Satellite& operator=(const Satellite& satellite) = default;
    virtual Satellite& operator=(Satellite&& satellite) = default;
    virtual Satellite* clone() const;
    Orbit getOrbit() const;
    Orbit* getOrbitPtr();
    virtual void logEvent(const std::string& name, const double& time);
    virtual void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    virtual void update(const double& seconds);
  private:
    Orbit orbit;
    Logger* logger; // singleton, should not be deleted
  };
}

#endif
