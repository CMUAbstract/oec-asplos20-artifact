// Transmit.cpp
// Transmit class implementation file
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
#include <algorithm>     // max, min
#include <array>         // array
#include <cstddef>       // NULL
#include <utility>       // move

// comsim
#include <DateTime.hpp>  // DateTime
#include <Log.hpp>       // Log
#include <Transmit.hpp>  // Transmit
#include <Vertex.hpp>    // Vertex
#include <utilities.hpp> // utilities

namespace comsim {
  Transmit::Transmit(
   const std::array<double,3>& posn, const double& powerW,
   const double& lineLossDB, const double& gainDB,
   const DateTime* const globalTime, const uint32_t& id, Log* const log
  ) : Vertex(), posn(posn), globalTime(globalTime), id(id), log(log) {
    this->setPower(powerW);
    this->setLineLoss(lineLossDB);
    this->setGain(gainDB);
  }

  Transmit::Transmit(const Transmit& transmit) : Vertex(transmit),
   posn(transmit.getPosn()), powerW(transmit.getPower()),
   lineLossFactor(transmit.getLineLoss()), gainFactor(transmit.getGain()),
   globalTime(transmit.getGlobalTime()), id(transmit.getID()),
   log(transmit.getLog()) {}

  Transmit::Transmit(Transmit&& transmit) : Vertex(std::move(transmit)),
   posn(transmit.posn), powerW(transmit.powerW),
   lineLossFactor(transmit.lineLossFactor), gainFactor(transmit.gainFactor),
   globalTime(transmit.globalTime), id(transmit.id), log(transmit.log) {
    transmit.globalTime = NULL;
    transmit.log = NULL;
  }

  Transmit::~Transmit() {
    this->globalTime = NULL;
    this->log = NULL;
  }

  Transmit& Transmit::operator=(const Transmit& transmit) {
    Transmit temp(transmit);
    *this = std::move(temp);
    return *this;
  }

  Transmit& Transmit::operator=(Transmit&& transmit) {
    this->Vertex::operator=(std::move(transmit));
    this->posn = transmit.posn;
    this->powerW = transmit.powerW;
    this->lineLossFactor = transmit.lineLossFactor;
    this->gainFactor = transmit.gainFactor;
    this->globalTime = transmit.globalTime;
    this->id = transmit.id;
    this->log = transmit.log;
    transmit.globalTime = NULL;
    transmit.log = NULL;
    return *this;
  }

  Transmit* Transmit::clone() const {
    return new Transmit(*this);
  }

  std::array<double,3> Transmit::getPosn() const {
    return this->posn;
  }

  double Transmit::getPower() const {
    return this->powerW;
  }

  double Transmit::getLineLoss() const {
    return this->lineLossFactor;
  }

  double Transmit::getGain() const {
    return this->gainFactor;
  }

  const DateTime* Transmit::getGlobalTime() const {
    return this->globalTime;
  }

  uint32_t Transmit::getID() const {
    return this->id;
  }

  Log* Transmit::getLog() const {
    return this->log;
  }

  void Transmit::setPosn(const std::array<double,3>& posn) {
    this->posn = posn;
  }

  void Transmit::setPower(const double& powerW) {
    this->powerW = std::max(0.0, powerW);
  }

  void Transmit::setLineLoss(const double& lineLossDB) {
    this->lineLossFactor = std::max(0.0,std::min(util::dB2Dec(lineLossDB),1.0));
  }

  void Transmit::setGain(const double& gainDB) {
    this->gainFactor = std::max(1.0,util::dB2Dec(gainDB));
  }

  void Transmit::update(const uint32_t& nanosecond) {
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(nanosecond);
  }

  void Transmit::update(const uint8_t& second, const uint32_t& nanosecond) {
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(second,nanosecond);
  }

  void Transmit::update(
   const uint8_t& minute, const uint8_t& second, const uint32_t& nanosecond
  ) {
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(minute,second,nanosecond);
  }

  void Transmit::update(
   const uint8_t& hour, const uint8_t& minute, const uint8_t& second,
   const uint32_t& nanosecond
  ) {
    // **It is expected that this->globalTime has already been updated**
    // Perform (possibly custom) update for localTime
    //this->localTime.update(minute,second,nanosecond);
  }
}
