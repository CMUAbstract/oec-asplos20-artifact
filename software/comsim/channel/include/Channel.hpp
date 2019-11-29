// Channel.hpp
// Channel class header file
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

#ifndef COMSIM_CHANNEL_HPP
#define COMSIM_CHANNEL_HPP

// Standard library
#include <array>           // array
#include <cstdint>         // uint64_t

// comsim
#include <ChannelType.hpp> // ChannelType
#include <DateTime.hpp>    // DateTime
#include <Edge.hpp>        // Edge
#include <ISim.hpp>        // Simulation interface
#include <Log.hpp>         // Log
#include <Receive.hpp>     // Receive
#include <Transmit.hpp>    // Transmit
#include <Vertex.hpp>      // Vertex

namespace comsim {
  class Channel: public ISim, public Edge {
  public:
    Channel(
     const Transmit* const transmit, const Receive* const receive,
     const double& centerFrequencyHz, const double& bandwidthHz,
     const DateTime* const globalTime, Log* const log=NULL
    );
    Channel(const Channel& channel);
    Channel(Channel&& channel);
    virtual ~Channel();
    virtual Channel& operator=(const Channel& channel);
    virtual Channel& operator=(Channel&& channel);
    virtual Channel* clone() const;
    const Transmit* getTransmit() const;
    const Receive* getReceive() const;
    double getCenterFrequency() const;        // Returns center frequency in Hz
    double getBandwidth() const;              // Returns bandwidth in Hz
    const DateTime* getGlobalTime() const;
    Log* getLog() const;
    ChannelType getChannelType() const;
    double getRange() const;                  // Returns range in km
    double getAtmosphericLoss() const;        // Return air loss factor (not dB)
    double getSystemNoiseTemperature() const; // Returns system noise temp (K)
    uint64_t getMaxBitsPerSec() const;
    uint64_t getBitsPerSec() const;
    void setBitsPerSec(const uint64_t& bitsPerSec);
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
    void setCenterFrequency(const double& centerFrequencyHz);
    void setBandwidth(const double& bandwidthHz);
    const Transmit* transmit;       // TX
    const Receive* receive;         // RX
    double centerFrequencyHz;       // center frequency in Hz
    double bandwidthHz;             // bandwidth in Hz
    const DateTime* globalTime;     // singleton, should not be deleted
    Log* log;                       // singleton, should not be deleted
    ChannelType channelType;        // Downlink, crosslink, or uplink
    double rangeKm;                 // TX-RX separation vector magnitude in km
    double atmosphericLossFactor;   // signal power loss factor due to air
    double systemNoiseTemperatureK; // system noise temperature T_s in Kelvin
    uint64_t maxBitsPerSec;         // Shannon-Hartley theorem limit
    uint64_t bitsPerSec;            // actual data rate
  };
}

#endif
