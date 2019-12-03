// Sensor.hpp
// Sensor class header file
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

#ifndef COMSIM_SENSOR_HPP
#define COMSIM_SENSOR_HPP

// Standard library
#include <array>        // array
#include <cstdint>      // uint32_t, uint64_t

// satsim
#include <DateTime.hpp> // DateTime
#include <ISim.hpp>     // Simulator interface
#include <Log.hpp>      // Log

namespace comsim {
  class Sensor: public ISim {
  public:
    Sensor(
     const DateTime* const globalTime, const uint32_t& id=0, Log* const log=NULL
    );
    Sensor(const Sensor& sensor);
    Sensor(Sensor&& sensor);
    virtual ~Sensor();
    virtual Sensor& operator=(const Sensor& sensor);
    virtual Sensor& operator=(Sensor&& sensor);
    virtual Sensor* clone() const;
    bool getSenseTrigger() const;
    uint64_t getBitsBuffered() const;
    uint64_t getBitsPerSense() const;
    std::array<double,3> getPrevSensePosn() const;
    DateTime getPrevSenseDateTime() const;
    std::array<double,3> getECIPosn() const;
    const DateTime* getGlobalTime() const;
    uint32_t getID() const;
    Log* getLog() const;
    void triggerSense(); // sets senseTrigger to true
    uint64_t drainBuffer(const uint64_t& bits); // returns value <= bits
    void setBitsPerSense(const uint64_t& bits);
    void setPrevSensePosn(const std::array<double,3>& eciPosn);
    void setPrevSenseDateTime(const DateTime& dateTime);
    void setECIPosn(const std::array<double,3>& eciPosn);
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
    bool senseTrigger;                  // If true, sense event at next update
    uint64_t bitsBuffered;              // bits of data buffered on device
    uint64_t bitsPerSense;              // bits per sense event
    std::array<double,3> prevSensePosn; // ECI position of most recent sense
    DateTime prevSenseDateTime;         // Date and time of most recent sense
    std::array<double,3> eciPosn;       // current ECI position
    const DateTime* globalTime;         // singleton, should not be deleted
    uint32_t id;                        // sensor identification number
    Log* log;                           // singleton, should not be deleted
  };
}

#endif
