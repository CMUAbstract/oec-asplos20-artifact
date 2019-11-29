// EHSystem.cpp
// EHSystem class implementation file
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
#include <algorithm>    // max
#include <cmath>        // pow, sqrt
#include <string>       // string
#include <utility>      // move

// satsim
#include <Logger.hpp>   // Logger
#include <EHSystem.hpp> // EHSystem

namespace satsim {
  EHSystem::EHSystem(
   const EnergyHarvester& energyHarvester, const Capacitor& capacitor,
   Logger* logger
  ) : energyHarvester(energyHarvester.clone()), capacitor(capacitor),
      logger(logger), totalPower_W(0.0), simTime_sec(0.0) {
    updateNodeVoltage(); // initializes this->nodeVoltage_V
  }

  EHSystem::EHSystem(const EHSystem& ehsystem) :
   energyHarvester(ehsystem.getEnergyHarvester()),
   capacitor(ehsystem.getCapacitor()), totalPower_W(ehsystem.getTotalPower()),
   nodeVoltage_V(ehsystem.getNodeVoltage()), simTime_sec(ehsystem.getSimTime()),
   logger(ehsystem.getLogger()) {
    std::vector<const EnergyConsumer*> energyConsumers =
     ehsystem.getEnergyConsumers();
    for(size_t i=0; i<energyConsumers.size(); i++) {
      this->energyConsumers.push_back(energyConsumers.at(i)->clone());
      delete energyConsumers.at(i);
    }
  }

  EHSystem::EHSystem(EHSystem&& ehsystem) :
   energyHarvester(ehsystem.energyHarvester),
   capacitor(std::move(ehsystem.capacitor)),
   nodeVoltage_V(ehsystem.nodeVoltage_V), simTime_sec(ehsystem.simTime_sec),
   logger(ehsystem.logger) {
    ehsystem.energyHarvester = NULL;
    ehsystem.logger = NULL;
    for(size_t i=0; i<ehsystem.energyConsumers.size(); i++) {
      this->energyConsumers.push_back(ehsystem.energyConsumers.at(i));
      ehsystem.energyConsumers.at(i) = NULL;
    }
  }

  EHSystem::~EHSystem() {
    delete this->energyHarvester;
    for(size_t i=0; i<this->energyConsumers.size(); i++) {
      delete this->energyConsumers.at(i);
    }
  }

  EHSystem& EHSystem::operator=(const EHSystem& ehsystem) {
    EHSystem temp(ehsystem);
    *this = std::move(temp);
    return *this;
  }

  EHSystem& EHSystem::operator=(EHSystem&& ehsystem) {
    delete this->energyHarvester;
    this->energyHarvester = ehsystem.energyHarvester;
    ehsystem.energyHarvester = NULL;
    this->capacitor = std::move(ehsystem.capacitor);
    this->logger = ehsystem.logger;
    ehsystem.logger = NULL;
    for(size_t i=0; i<this->energyConsumers.size(); i++) {
      delete this->energyConsumers.at(i);
    }
    this->energyConsumers.clear();
    this->energyConsumers =
     std::vector<EnergyConsumer*>(ehsystem.energyConsumers.size());
    for(size_t i=0; i<ehsystem.energyConsumers.size(); i++) {
      this->energyConsumers.at(i) = ehsystem.energyConsumers.at(i);
      ehsystem.energyConsumers.at(i) = NULL;
    }
    return *this;
  }

  EnergyHarvester* EHSystem::getEnergyHarvester() const {
    return this->energyHarvester->clone();
  }

  Capacitor EHSystem::getCapacitor() const {
    return this->capacitor;
  }

  std::vector<const EnergyConsumer*> EHSystem::getEnergyConsumers() const {
    std::vector<const EnergyConsumer*> energyConsumers;
    for(size_t i=0; i<this->energyConsumers.size(); i++) {
      energyConsumers.push_back(this->energyConsumers.at(i)->clone());
    }
    return energyConsumers;
  }

  double EHSystem::getTotalPower() const {
    return this->totalPower_W;
  }

  double EHSystem::getNodeVoltage() const {
    return this->nodeVoltage_V;
  }

  double EHSystem::getSimTime() const {
    return this->simTime_sec;
  }

  // Send the actual pointers to allow for energy consumer state updates
  std::vector<EnergyConsumer*> EHSystem::getEnergyConsumers() {
    return this->energyConsumers;
  }

  Logger* EHSystem::getLogger() const {
    return this->logger;
  }

  void EHSystem::addEnergyConsumer(const EnergyConsumer& energyConsumer) {
    this->energyConsumers.push_back(energyConsumer.clone());
  }

  void EHSystem::logEvent(const std::string& name, const double& time) {
    if(this->logger!=NULL) {
      this->logger->logEvent(name, time);
    }
  }

  void EHSystem::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->logger!=NULL) {
      this->logger->logMeasurement(name, time, measurement);
    }
  }

  void EHSystem::update(const double& seconds) {
    // Sanitize input
    double sanitizedSeconds = std::max(0.0,seconds);
    // Update this->nodeVoltage_V (no time dep, required for all other updates)
    updateNodeVoltage();
    // Update energy harvester and get the current
    this->energyHarvester->setVoltage(this->nodeVoltage_V);
    energyHarvester->update(sanitizedSeconds);
    double harvestCurrent_A = energyHarvester->getCurrent();
    // Update each energy consuming device and get the total current draw
    double deviceCurrent_A = 0.0;
    for(size_t i=0; i<this->energyConsumers.size(); i++) {
      energyConsumers.at(i)->setVoltage(this->nodeVoltage_V);
      energyConsumers.at(i)->update(sanitizedSeconds);
      deviceCurrent_A += energyConsumers.at(i)->getCurrent();
    }
    updateTotalPower(); // call this anytime energy consumers may have changed
    // Update capacitor
    capacitor.setCurrent(harvestCurrent_A-deviceCurrent_A);
    capacitor.update(sanitizedSeconds);
    // Update simulation time
    this->simTime_sec += sanitizedSeconds;
  }

  double EHSystem::calculateDiscriminant() const {
    return
     std::pow(
      energyHarvester->getCurrent()*capacitor.getEsr() +
      capacitor.getCharge()/capacitor.getCapacity(), 2.0
     ) - 4.0*capacitor.getEsr()*this->totalPower_W;
  }

  double EHSystem::calculateNodeVoltage() const {
    return
     (
      energyHarvester->getCurrent()*capacitor.getEsr() +
      capacitor.getCharge()/capacitor.getCapacity() +
      std::sqrt(calculateDiscriminant())
     )*0.5;
  }

  void EHSystem::updateTotalPower() {
    double tally_W = 0.0;
    for(size_t i=0; i<this->energyConsumers.size(); i++) {
      tally_W += energyConsumers.at(i)->getPower();
    }
    this->totalPower_W = tally_W;
  }

  void EHSystem::updateNodeVoltage() {
    if(calculateDiscriminant()<0.0) {
      for(size_t i=0; i<this->energyConsumers.size(); i++) {
        energyConsumers.at(i)->setOff();
      }
      updateTotalPower();
      logEvent("ehs-blackout", this->simTime_sec);
    }
    this->nodeVoltage_V = calculateNodeVoltage();
  }
}
