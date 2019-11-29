// Transmit.hpp
// Transmit class header file
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

#ifndef COMSIM_TRANSMIT_HPP
#define COMSIM_TRANSMIT_HPP

// Standard library
#include <array>        // array

// comsim
#include <DateTime.hpp> // DateTime
#include <ISim.hpp>     // Simulation interface
#include <Log.hpp>      // Log
#include <Vertex.hpp>   // Vertex

namespace comsim {
  class Transmit: public ISim, public Vertex {
  public:
    Transmit(
     const std::array<double,3>& posn, const double& powerW,
     const double& lineLossDB, const double& gainDB,
     const DateTime* const globalTime, const uint32_t& id=0, Log* const log=NULL
    );
    Transmit(const Transmit& transmit);
    Transmit(Transmit&& transmit);
    virtual ~Transmit();
    virtual Transmit& operator=(const Transmit& transmit);
    virtual Transmit& operator=(Transmit&& transmit);
    virtual Transmit* clone() const;
    std::array<double,3> getPosn() const;
    double getPower() const;    // Returns power in Watts
    double getLineLoss() const; // Returns line loss factor (not dB)
    double getGain() const;     // Returns gain factor (not dB)
    const DateTime* getGlobalTime() const;
    uint32_t getID() const;
    Log* getLog() const;
    void setPosn(const std::array<double,3>& posn);
    void setPower(const double& powerW);
    void setLineLoss(const double& lineLossDB);
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
    std::array<double,3> posn;  // Three-dimensional position of TX ANT
    double powerW;              // TX power in Watt
    double lineLossFactor;      // line loss between TX and ANT
    double gainFactor;          // maximum TX antenna gain
    const DateTime* globalTime; // singleton, should not be deleted
    uint32_t id;                // identification number
    Log* log;                   // singleton, should not be deleted
  };
}

#endif
