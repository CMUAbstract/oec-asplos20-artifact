// Orbit.hpp
// Orbit class header file
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
