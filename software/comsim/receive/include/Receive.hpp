// Receive.hpp
// Receive class header file
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

#ifndef COMSIM_RECEIVE_HPP
#define COMSIM_RECEIVE_HPP

// Standard library
#include <array>        // array

// comsim
#include <DateTime.hpp> // DateTime
#include <ISim.hpp>     // Simulation interface
#include <Log.hpp>      // Log
#include <Vertex.hpp>   // Vertex

namespace comsim {
  class Receive: public ISim, public Vertex {
  public:
    Receive(
     const std::array<double,3>& posn, const double& gainDB,
     const DateTime* const globalTime, const uint32_t& id=0, Log* const log=NULL
    );
    Receive(const Receive& receive);
    Receive(Receive&& receive);
    virtual ~Receive();
    virtual Receive& operator=(const Receive& receive);
    virtual Receive& operator=(Receive&& receive);
    virtual Receive* clone() const;
    std::array<double,3> getPosn() const;
    double getGain() const; // Returns gain factor (not dB)
    const DateTime* getGlobalTime() const;
    uint32_t getID() const;
    Log* getLog() const;
    void setPosn(const std::array<double,3>& posn);
    void setGain(const double& gainDB);
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
    std::array<double,3> posn;  // Three-dimensional position of RX ANT
    double gainFactor;          // maximum RX antenna gain
    const DateTime* globalTime; // singleton, should not be deleted
    uint32_t id;                // identification number
    Log* log;                   // singleton, should not be deleted
  };
}

#endif
