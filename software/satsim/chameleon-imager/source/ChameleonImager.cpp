// ChameleonImager.cpp
// Chameleon Imager class implementation file
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

// Standard library
#include <algorithm>           // max

// satsim
#include <EnergyConsumer.hpp>  // EnergyConsumer
#include <ChameleonImager.hpp> // ChameleonImager
#include <Logger.hpp>          // Logger

namespace satsim {
  const double ChameleonImager::imagingDuration_sec = 0.031260; // 32 fps
  const double ChameleonImager::readoutDuration_sec = 0.838860; // ~25.17 MB @ 240 Mbps

  ChameleonImager::ChameleonImager(
   const double& initialVoltage_V, const PowerState& initialPowerState,
   Logger* logger
  ) : EnergyConsumer(initialVoltage_V, 0.0, logger),
      powerState(initialPowerState), simTime_sec(0.0), imagingTime_sec(0.0),
      readoutTime_sec(0.0), workerId(0) {
    this->setPower(getWatt(this->powerState));
  }

  ChameleonImager* ChameleonImager::clone() const {
    return new ChameleonImager(*this);
  }

  double ChameleonImager::getSimTime() const {
    return this->simTime_sec;
  }

  void ChameleonImager::setSimTime(const double& seconds) {
    this->simTime_sec = std::max(0.0,seconds);
  }

  size_t ChameleonImager::getWorkerId() const {
    return this->workerId;
  }

  void ChameleonImager::setWorkerId(const size_t& id) {
    this->workerId = id;
  }

  size_t ChameleonImager::getClaimedJobCount() const {
    return this->imagingFifo.size()+this->readoutFifo.size();
  }

  std::deque<Job*> ChameleonImager::getClaimedJobs() {
    std::deque<Job*> claimedJobs;
    for(size_t i=0; i<this->readoutFifo.size(); i++) {
      claimedJobs.push_back(this->readoutFifo.at(i));
    }
    for(size_t i=0; i<this->imagingFifo.size(); i++) {
      claimedJobs.push_back(this->imagingFifo.at(i));
    }
    return claimedJobs;
  }

  void ChameleonImager::addClaimedJob(Job* job) {
    this->imagingFifo.push_back(job);
  }

  size_t ChameleonImager::getCompletedJobCount() const {
    return this->readyImages.size();
  }

  std::deque<Job*> ChameleonImager::getCompletedJobs() {
    return this->readyImages;
  }

  bool ChameleonImager::isIdle() const {
    if(this->powerState==PowerState::IDLE) {
      return true;
    } else {
      return false;
    }
  }

  bool ChameleonImager::hasImage() const {
    if(this->readyImages.size()>0) {
      return true;
    } else {
      return false;
    }
  }

  Job* ChameleonImager::dequeImage() {
    Job* image = NULL;
    if(this->readyImages.size()>0) {
      image = readyImages.front();
      readyImages.pop_front();
    }
    return image;
  }

  void ChameleonImager::update(const double& seconds) {
    // Sanitize input
    double sanitizedSeconds = std::max(0.0,seconds);
    // State machine logic
    // If power state is OFF
    if(this->powerState==ChameleonImager::PowerState::OFF) {
      // Only wake up if voltage is good
      if(this->getVoltage()>=5.0) {
        // OFF -> READOUT if readout was interrupted
        if(this->readoutFifo.size()!=0) {
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-off-stop",
          // this->simTime_sec+sanitizedSeconds
          //);
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-readout-start",
          // this->simTime_sec+sanitizedSeconds
          //);
          setPowerState(ChameleonImager::PowerState::READOUT);
        }
        // otherwise OFF -> IDLE
        else {
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-off-stop",
          // this->simTime_sec+sanitizedSeconds
          //);
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-idle-start",
          // this->simTime_sec+sanitizedSeconds
          //);
          setPowerState(ChameleonImager::PowerState::IDLE);
        }
      }
    }
    // otherwise if power state is IDLE
    else if(this->powerState==ChameleonImager::PowerState::IDLE) {
      // IDLE -> OFF if voltage is bad
      if(this->getVoltage()<5.0) {
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-idle-stop",
        // this->simTime_sec+sanitizedSeconds
        //);
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-off-start",
        // this->simTime_sec+sanitizedSeconds
        //);
        setPowerState(ChameleonImager::PowerState::OFF);
      }
      // otherwise IDLE -> IMAGING if the imaging FIFO has been populated
      else if(this->imagingFifo.size()!=0) {
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-idle-stop",
        // this->simTime_sec+sanitizedSeconds
        //);
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-imaging-start",
        // this->simTime_sec+sanitizedSeconds
        //);
        setPowerState(ChameleonImager::PowerState::IMAGING);
      }
    }
    // otherwise if power state is IMAGING
    else if(this->powerState==ChameleonImager::PowerState::IMAGING) {
      // IMAGING -> OFF if voltage is bad
      if(this->getVoltage()<5.0) {
        // clear imagingFifo
        for(size_t i=0; i<imagingFifo.size(); i++) {
          this->imagingFifo.at(i)->unclaimTasks(this->workerId);
        }
        this->imagingFifo.clear(); // Cannot continue on wake
        // end clear imagingFifo
        this->imagingTime_sec = 0.0;
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-imaging-stop",
        // this->simTime_sec+sanitizedSeconds
        //);
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-off-start",
        // this->simTime_sec+sanitizedSeconds
        //);
        setPowerState(ChameleonImager::PowerState::OFF);
      }
      // IMAGING state update
      else {
        this->imagingTime_sec = this->imagingTime_sec+sanitizedSeconds;
        size_t newImagingEventCount = 0;
        while(
         this->imagingTime_sec>=this->imagingDuration_sec &&
         this->imagingFifo.size() > 0
        ) {
          this->readoutFifo.push_back(this->imagingFifo.front());
          this->imagingFifo.pop_front();
          this->imagingTime_sec -= this->imagingDuration_sec;
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-capture-gtf-"+
          // std::to_string(this->readoutFifo.back()->getJobId()),
          // this->simTime_sec+newImagingEventCount*this->imagingDuration_sec
          //);
          newImagingEventCount += 1;
        }
        // if this->imagingFifo.size() == 0, transition to READOUT
        if(this->imagingFifo.size()==0) {
          this->imagingTime_sec = 0.0;
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-imaging-stop",
          // this->simTime_sec+sanitizedSeconds
          //);
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-readout-start",
          // this->simTime_sec+sanitizedSeconds
          //);
          setPowerState(ChameleonImager::PowerState::READOUT);
        }
      }
    }
    // otherwise if power state is READOUT
    else if(this->powerState==ChameleonImager::PowerState::READOUT) {
      // IMAGING -> OFF if voltage is bad
      if(this->getVoltage()<5.0) {
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-readout-stop",
        // this->simTime_sec+sanitizedSeconds
        //);
        //this->logEvent(
        // "chamgr-"+std::to_string(this->workerId)+"-off-start",
        // this->simTime_sec+sanitizedSeconds
        //);
        setPowerState(ChameleonImager::PowerState::OFF);
      }
      // READOUT state update
      else {
        this->readoutTime_sec = this->readoutTime_sec+sanitizedSeconds;
        size_t newReadoutEventCount = 0;
        while(
         this->readoutTime_sec>=this->readoutDuration_sec &&
         this->readoutFifo.size() > 0
        ) {
          this->readyImages.push_back(this->readoutFifo.front());
          this->readoutFifo.pop_front();
          this->readoutTime_sec -= this->readoutDuration_sec;
          this->logEvent(
           "chamgr-"+std::to_string(this->workerId)+"-readout-gtf-"+
           std::to_string(this->readyImages.back()->getJobId()),
           this->simTime_sec+newReadoutEventCount*this->readoutDuration_sec
          );
          newReadoutEventCount += 1;
        }
        // if this->readoutFifo.size() == 0, transition to IDLE
        if(this->readoutFifo.size()==0) {
          this->readoutTime_sec = 0.0;
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-readout-stop",
          // this->simTime_sec+sanitizedSeconds
          //);
          //this->logEvent(
          // "chamgr-"+std::to_string(this->workerId)+"-idle-start",
          // this->simTime_sec+sanitizedSeconds
          //);
          setPowerState(ChameleonImager::PowerState::IDLE);
        }
      }
    }
    // Update simulation time
    this->simTime_sec += sanitizedSeconds;
  }

  double ChameleonImager::getWatt(const ChameleonImager::PowerState& powerState) const {
    double watt = 0.0;
    switch(powerState) {
      case ChameleonImager::PowerState::OFF:
        watt = 0.0;
        break;
      case ChameleonImager::PowerState::IDLE:
        watt = 0.0;
        break;
      case ChameleonImager::PowerState::IMAGING:
        watt = 3.5;
        break;
      case ChameleonImager::PowerState::READOUT:
        watt = 2.5;
        break;
      default:
        watt = 0.0;
        break;
    }
    return watt;
  }

  void ChameleonImager::setPowerState(const PowerState& powerState) {
    this->powerState = powerState;
    this->setPower(getWatt(this->powerState));
  }
}
