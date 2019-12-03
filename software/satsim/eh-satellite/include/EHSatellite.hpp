// EHSatellite.hpp
// EHSatellite class header file
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
