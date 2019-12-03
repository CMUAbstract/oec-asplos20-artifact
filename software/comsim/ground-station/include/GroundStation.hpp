// GroundStation.hpp
// GroundStation class header file
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

#ifndef COMSIM_GROUND_STATION_HPP
#define COMSIM_GROUND_STATION_HPP

// Standard library
#include <array>         // array

// comsim
#include <DateTime.hpp>  // DateTime
#include <ISim.hpp>      // Simulator interface
#include <Log.hpp>       // Log
#include <LogLevel.hpp>  // LogLevel

namespace comsim {
  class GroundStation: public ISim {
  public:
    // lat: latitude in degrees; ranges from -90.0 (south) to +90.0 (north)
    //      Some functions in the comsim utilities may not function properly at
    //      +/-90.0 degrees due to singularities
    // lon: longitude in degrees; ranges from -180.0 (west) to +180.0 (east)
    // hae: height above the ellipsoid in km
    GroundStation(
     const double& lat, const double& lon, const double& hae,
     const DateTime* const dateTime, const uint32_t& id=0, Log* const log=NULL
    );
    GroundStation(const GroundStation& groundStation);
    GroundStation(GroundStation&& groundStation);
    virtual ~GroundStation();
    virtual GroundStation& operator=(const GroundStation& groundStation);
    virtual GroundStation& operator=(GroundStation&& groundStation);
    virtual GroundStation* clone() const;
    double getLatitude() const;  // returns latitude in radians
    double getLongitude() const; // returns longitude in radians
    double getHAE() const;       // returns height above ellipsoid in kilometers
    std::array<double,3> getECIPosn() const;
    DateTime getLocalTime() const;
    const DateTime* getGlobalTime() const;
    uint32_t getID() const;
    Log* getLog() const;
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
    double lat;                   // latitude in radians
    double lon;                   // longitude in radians
    double hae;                   // height above ellipsoid in kilometers
    std::array<double,3> eciPosn; // (x,y,z) position in ECI coordinate frame
    DateTime  localTime;          // Shadow date/time can be used for fudging
    const DateTime* globalTime;   // singleton, should not be deleted
    uint32_t id;                  // ground station identification number
    Log* log;                     // singleton, should not be deleted
  };
}

#endif
