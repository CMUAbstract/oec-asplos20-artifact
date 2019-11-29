// Channel.cpp
// Channel class implementation file
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

// Standard library
#include <algorithm>       // max, min
#include <array>           // array
#include <cstddef>         // NULL
#include <utility>         // move

// comsim
#include <Channel.hpp>     // Channel
#include <ChannelType.hpp> // ChannelType
#include <constants.hpp>   // constants
#include <DateTime.hpp>    // DateTime
#include <Edge.hpp>        // Edge
#include <Log.hpp>         // Log
#include <Receive.hpp>     // Receive
#include <Transmit.hpp>    // Transmit
#include <utilities.hpp>   // utilities
#include <Vertex.hpp>      // Vertex

namespace comsim {
  Channel::Channel(
   const Transmit* const transmit, const Receive* const receive,
   const double& centerFrequencyHz, const double& bandwidthHz,
   const DateTime* const globalTime, Log* const log
  ) : Edge(
   static_cast<const Vertex* const>(transmit),
   static_cast<const Vertex* const>(receive)
  ), transmit(transmit), receive(receive), globalTime(globalTime), log(log) {
    this->setCenterFrequency(centerFrequencyHz);
    this->setBandwidth(bandwidthHz);
    if(
     util::magnitude(this->transmit->getPosn()) > cnst::WGS_84_A+98.0 &&
     util::magnitude(this->receive->getPosn()) <= cnst::WGS_84_A+98.0
    ) {
      this->channelType = ChannelType::DOWNLINK;
    } else if(
     util::magnitude(this->transmit->getPosn()) > cnst::WGS_84_A+98.0 &&
     util::magnitude(this->receive->getPosn())  > cnst::WGS_84_A+98.0
    ) {
      this->channelType = ChannelType::CROSSLINK;
    } else if(
     util::magnitude(this->transmit->getPosn())<= cnst::WGS_84_A+98.0 &&
     util::magnitude(this->receive->getPosn())  > cnst::WGS_84_A+98.0
    ) {
      this->channelType = ChannelType::UPLINK;
    } else {
      this->channelType = ChannelType::UNSPECIFIED;
    }
    this->rangeKm = util::magnitude(util::calcSeparationVector(
     this->receive->getPosn(), this->transmit->getPosn()
    ));
    this->atmosphericLossFactor = util::calcAtmosphericLoss();
    this->systemNoiseTemperatureK = util::calcSystemNoiseTemp(
     this->channelType, this->centerFrequencyHz
    );
    this->maxBitsPerSec = util::calcMaxBitsPerSec(
     this->transmit->getPower(), this->transmit->getLineLoss(),
     this->transmit->getGain(), this->atmosphericLossFactor,
     this->receive->getGain(), this->centerFrequencyHz, this->rangeKm,
     this->systemNoiseTemperatureK, this->bandwidthHz
    );
    this->bitsPerSec = this->maxBitsPerSec;
  }

  Channel::Channel(const Channel& channel) : Edge(channel),
   transmit(channel.getTransmit()), receive(channel.getReceive()),
   centerFrequencyHz(channel.getCenterFrequency()),
   bandwidthHz(channel.getBandwidth()), globalTime(channel.getGlobalTime()),
   log(channel.getLog()), channelType(channel.getChannelType()),
   rangeKm(channel.getRange()),
   atmosphericLossFactor(channel.getAtmosphericLoss()),
   systemNoiseTemperatureK(channel.getSystemNoiseTemperature()),
   maxBitsPerSec(channel.getMaxBitsPerSec()),
   bitsPerSec(channel.getBitsPerSec()) {}

  Channel::Channel(Channel&& channel) : Edge(std::move(channel)),
   transmit(channel.transmit), receive(channel.receive),
   centerFrequencyHz(channel.centerFrequencyHz),
   bandwidthHz(channel.bandwidthHz), globalTime(channel.globalTime),
   log(channel.log), channelType(channel.channelType), rangeKm(channel.rangeKm),
   atmosphericLossFactor(channel.atmosphericLossFactor),
   systemNoiseTemperatureK(channel.systemNoiseTemperatureK),
   maxBitsPerSec(channel.maxBitsPerSec), bitsPerSec(channel.bitsPerSec) {
    channel.transmit = NULL;
    channel.receive = NULL;
    channel.globalTime = NULL;
    channel.log = NULL;
  }

  Channel::~Channel() {
    this->transmit = NULL;
    this->receive = NULL;
    this->globalTime = NULL;
    this->log = NULL;
  }

  Channel& Channel::operator=(const Channel& channel) {
    Channel temp(channel);
    *this = std::move(temp);
    return *this;
  }

  Channel& Channel::operator=(Channel&& channel) {
    this->Edge::operator=(std::move(channel));
    this->transmit = channel.transmit;
    this->receive = channel.receive;
    this->centerFrequencyHz = channel.centerFrequencyHz;
    this->bandwidthHz = channel.bandwidthHz;
    this->globalTime = channel.globalTime;
    this->log = channel.log;
    this->channelType = channel.channelType;
    this->rangeKm = channel.rangeKm;
    this->atmosphericLossFactor = channel.atmosphericLossFactor;
    this->systemNoiseTemperatureK = channel.systemNoiseTemperatureK;
    this->maxBitsPerSec = channel.maxBitsPerSec;
    this->bitsPerSec = channel.bitsPerSec;
    channel.transmit = NULL;
    channel.receive = NULL;
    channel.globalTime = NULL;
    channel.log = NULL;
    return *this;
  }

  Channel* Channel::clone() const {
    return new Channel(*this);
  }

  const Transmit* Channel::getTransmit() const {
    return this->transmit;
  }

  const Receive* Channel::getReceive() const {
    return this->receive;
  }

  double Channel::getCenterFrequency() const {
    return this->centerFrequencyHz;
  }

  double Channel::getBandwidth() const {
    return this->bandwidthHz;
  }

  const DateTime* Channel::getGlobalTime() const {
    return this->globalTime;
  }

  Log* Channel::getLog() const {
    return this->log;
  }

  ChannelType Channel::getChannelType() const {
    return this->channelType;
  }

  double Channel::getRange() const {
    return this->rangeKm;
  }

  double Channel::getAtmosphericLoss() const {
    return this->atmosphericLossFactor;
  }

  double Channel::getSystemNoiseTemperature() const {
    return this->systemNoiseTemperatureK;
  }

  uint64_t Channel::getMaxBitsPerSec() const {
    return this->maxBitsPerSec;
  }

  uint64_t Channel::getBitsPerSec() const {
    return this->bitsPerSec;
  }

  void Channel::setBitsPerSec(const uint64_t& bitsPerSec) {
    this->bitsPerSec = std::min(bitsPerSec, this->maxBitsPerSec);
  }

  void Channel::update(const uint32_t& nanosecond) {
    // stuff...
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(nanosecond);
  }

  void Channel::update(const uint8_t& second, const uint32_t& nanosecond) {
    // stuff...
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(second,nanosecond);
  }

  void Channel::update(
   const uint8_t& minute, const uint8_t& second, const uint32_t& nanosecond
  ) {
    // stuff...
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(minute,second,nanosecond);
  }

  void Channel::update(
   const uint8_t& hour, const uint8_t& minute, const uint8_t& second,
   const uint32_t& nanosecond
  ) {
    // stuff...
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(minute,second,nanosecond);
  }

  void Channel::setCenterFrequency(const double& centerFrequencyHz) {
    this->centerFrequencyHz = std::max(0.0, centerFrequencyHz);
  }

  void Channel::setBandwidth(const double& bandwidthHz) {
    this->bandwidthHz =
     std::max(0.0, std::min(bandwidthHz, this->centerFrequencyHz*2.0));
  }
}
