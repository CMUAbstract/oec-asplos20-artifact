// Orbit.hpp
// Orbit class header file
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

#ifndef SATSIM_ORBIT_HPP
#define SATSIM_ORBIT_HPP

// Standard library
#include <string>     // string

// satsim
#include <ILog.hpp>   // Logger interface
#include <ISim.hpp>   // Simulator interface
#include <Logger.hpp> // Logger

namespace satsim {
  class Orbit: public ILog, public ISim {
  public:
    static const double TAU;
    Orbit(
     const double& period_sec, const double& posn_rad, Logger* logger=NULL
    );
    double getPeriod() const;
    double getPosn() const;
    void logEvent(const std::string& name, const double& time);
    void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    void update(const double& seconds);
  private:
    double period_sec;
    double posn_rad;
    Logger* logger;    // singleton, should not be deleted
  };
}

#endif
