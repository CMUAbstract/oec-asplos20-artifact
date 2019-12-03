// Satellite.hpp
// Satellite class header file
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

#ifndef COMSIM_SATELLITE_HPP
#define COMSIM_SATELLITE_HPP

// Standard library
#include <string>       // string

// satsim
#include <DateTime.hpp> // DateTime
#include <ISim.hpp>     // Simulator interface
#include <Log.hpp>      // Log

namespace comsim {
  class Satellite: public ISim {
  public:
    Satellite(
     const std::string& tleFile, const DateTime* const globalTime,
     Log* const log=NULL
    );
    Satellite(const Satellite& satellite);
    Satellite(Satellite&& satellite);
    virtual ~Satellite();
    virtual Satellite& operator=(const Satellite& satellite);
    virtual Satellite& operator=(Satellite&& satellite);
    virtual Satellite* clone() const;
    uint32_t getCatalogNumber() const;
    DateTime getTLEEpoch() const;
    float getBstar() const;
    float getInclination() const;
    float getRAAN() const;
    float getEccentricity() const;
    float getArgOfPerigee() const;
    float getMeanAnomaly() const;
    float getMeanMotion() const;
    std::array<double,3> getECIPosn() const;
    DateTime getLocalTime() const;
    const DateTime* getGlobalTime() const;
    Log* getLog() const;
    void setCatalogNumber(const uint32_t& catalogNumber);
    void setLocalTime(const DateTime& localTime);
    virtual void update(const uint32_t& nanosecond);
    virtual void update(const uint8_t& second, const uint32_t& nanosecond);
    virtual void update(
     const uint8_t& minute, const uint8_t& second, const uint32_t& nanosecond
    );
    virtual void update(
     const uint8_t& hour, const uint8_t& minute, const uint8_t& second,
     const uint32_t& nanosecond
    );
  private:
    uint32_t catalogNumber;
    DateTime tleEpoch;
    float bstar;                  // inverse Earth radians
    float inclination;            // radians
    float raan;                   // right ascension of node in radians
    float eccentricity;           // unitless
    float argOfPerigee;           // radians
    float meanAnomaly;            // radians
    float meanMotion;             // radians per minute
    std::array<double,3> eciPosn; // ECI position at current local time
    DateTime localTime;           // To be used by subclasses for fudge tricks
    const DateTime* globalTime;   // singleton, should not be deleted
    Log* log;                     // singleton, should not be deleted
  };
}

#endif
