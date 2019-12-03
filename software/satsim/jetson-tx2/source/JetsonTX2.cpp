// JetsonTX2.cpp
// Jetson TX2 class implementation file
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
#include <algorithm>          // max
#include <cstddef>            // size_t

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <JetsonTX2.hpp>      // JetsonTX2
#include <Logger.hpp>         // Logger

namespace satsim {
  const double JetsonTX2::detectDuration_sec = 0.044860; // Seconds per detect

  JetsonTX2::JetsonTX2(
   const double& initialVoltage_V, const PowerState& initialPowerState,
   Logger* logger
  ) : EnergyConsumer(initialVoltage_V, 0.0, logger),
      powerState(initialPowerState), simTime_sec(0.0), detectTime_sec(0.0),
      workerId(0), beginFlag(true) {
    this->setPower(getWatt(this->powerState));
  }

  JetsonTX2* JetsonTX2::clone() const {
    return new JetsonTX2(*this);
  }

  double JetsonTX2::getSimTime() const {
    return this->simTime_sec;
  }

  void JetsonTX2::setSimTime(const double& seconds) {
    this->simTime_sec = std::max(0.0,seconds);
  }

  size_t JetsonTX2::getWorkerId() const {
    return this->workerId;
  }

  void JetsonTX2::setWorkerId(const size_t& id) {
    this->workerId = id;
  }

  size_t JetsonTX2::getClaimedJobCount() const {
    return this->claimedJobs.size();
  }

  std::deque<Job*> JetsonTX2::getClaimedJobs() {
    return claimedJobs;
  }

  void JetsonTX2::addClaimedJob(Job* job) {
    this->claimedJobs.push_back(job);
  }

  size_t JetsonTX2::getCompletedJobCount() const {
    return this->completedJobs.size();
  }

  std::deque<Job*> JetsonTX2::getCompletedJobs() {
    return this->completedJobs;
  }

  bool JetsonTX2::isIdle() const {
    if(this->powerState==PowerState::IDLE) {
      return true;
    } else {
      return false;
    }
  }

  void JetsonTX2::update(const double& seconds) {
    // Sanitize input
    double sanitizedSeconds = std::max(0.0,seconds);
    // State machine logic
    // If power state is OFF
    if(this->powerState==JetsonTX2::PowerState::OFF) {
      // Only wake up if voltage is good
      if(this->getVoltage()>=6.75) {
        // OFF -> DETECT if detection was interrupted
        if(this->claimedJobs.size()!=0) {
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-off-stop",
           this->simTime_sec+sanitizedSeconds
          );
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-detect-start",
           this->simTime_sec+sanitizedSeconds
          );
          setPowerState(JetsonTX2::PowerState::DETECT);
        }
        // otherwise OFF -> IDLE
        else {
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-off-stop",
           this->simTime_sec+sanitizedSeconds
          );
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-idle-start",
           this->simTime_sec+sanitizedSeconds
          );
          setPowerState(JetsonTX2::PowerState::IDLE);
        }
      }
    }
    // otherwise if power state is SLEEP
    else if(this->powerState==JetsonTX2::PowerState::SLEEP) {
      // SLEEP -> OFF if voltage is bad
      if(this->getVoltage()<5.5) {
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-sleep-stop",
         this->simTime_sec+sanitizedSeconds
        );
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-off-start",
         this->simTime_sec+sanitizedSeconds
        );
        setPowerState(JetsonTX2::PowerState::OFF);
      }
      // otherwise if voltage is good
      else if(this->getVoltage()>=6.75) {
        // SLEEP -> DETECT if detection was interrupted
        if(this->claimedJobs.size()!=0) {
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-sleep-stop",
           this->simTime_sec+sanitizedSeconds
          );
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-detect-start",
           this->simTime_sec+sanitizedSeconds
          );
          setPowerState(JetsonTX2::PowerState::DETECT);
        }
        // otherwise SLEEP -> IDLE
        else {
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-sleep-stop",
           this->simTime_sec+sanitizedSeconds
          );
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-idle-start",
           this->simTime_sec+sanitizedSeconds
          );
          setPowerState(JetsonTX2::PowerState::IDLE);
        }
      }
    }
    // otherwise if power state is IDLE
    else if(this->powerState==JetsonTX2::PowerState::IDLE) {
      // IDLE -> OFF if voltage is bad
      if(this->getVoltage()<5.5) {
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-idle-stop",
         this->simTime_sec+sanitizedSeconds
        );
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-off-start",
         this->simTime_sec+sanitizedSeconds
        );
        setPowerState(JetsonTX2::PowerState::OFF);
      }
      // IDLE -> SLEEP if voltage is low
      else if(this->getVoltage()<5.75) {
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-idle-stop",
         this->simTime_sec+sanitizedSeconds
        );
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-sleep-start",
         this->simTime_sec+sanitizedSeconds
        );
        setPowerState(JetsonTX2::PowerState::SLEEP);
      }
      // otherwise IDLE -> DETECT if claimed jobs has been populated
      else if(this->claimedJobs.size()!=0) {
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-idle-stop",
         this->simTime_sec+sanitizedSeconds
        );
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-detect-start",
         this->simTime_sec+sanitizedSeconds
        );
        setPowerState(JetsonTX2::PowerState::DETECT);
      }
    }
    // otherwise if power state is DETECT
    else if(this->powerState==JetsonTX2::PowerState::DETECT) {
      // DETECT -> OFF if voltage is bad
      if(this->getVoltage()<5.5) {
        this->detectTime_sec = 0.0;
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-detect-stop",
         this->simTime_sec+sanitizedSeconds
        );
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-off-start",
         this->simTime_sec+sanitizedSeconds
        );
        setPowerState(JetsonTX2::PowerState::OFF);
      }
      // DETECT -> SLEEP if voltage is low
      else if(this->getVoltage()<5.75) {
        this->detectTime_sec = 0.0;
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-detect-stop",
         this->simTime_sec+sanitizedSeconds
        );
        this->logEvent(
         "jetson-"+std::to_string(this->workerId)+"-sleep-start",
         this->simTime_sec+sanitizedSeconds
        );
        setPowerState(JetsonTX2::PowerState::SLEEP);
      }
      // DETECT state update
      else {
        if(this->beginFlag) {
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-begin-gtf-"+
           std::to_string(this->claimedJobs.front()->getJobId()),
           this->simTime_sec
          );
          this->beginFlag = false;
        }
        this->detectTime_sec = this->detectTime_sec+sanitizedSeconds;
        size_t newDetectEventCount = 0;
        while(
         this->detectTime_sec>=this->detectDuration_sec &&
         this->claimedJobs.size() > 0
        ) {
          this->claimedJobs.front()->completeTask(this->workerId);
          if(this->claimedJobs.front()->getClaimedTaskCount(this->workerId)==0){
            this->completedJobs.push_back(this->claimedJobs.front());
            claimedJobs.pop_front();
            this->beginFlag = true;
            //this->logEvent(
            // "jetson-"+std::to_string(this->workerId)+"-detect-gtf-"+
            // std::to_string(this->completedJobs.back()->getJobId()),
            // this->simTime_sec+newDetectEventCount*this->detectDuration_sec
            //);
            this->logEvent(
             "jetson-"+std::to_string(this->workerId)+"-complete-gtf-"+
             std::to_string(this->completedJobs.back()->getJobId()),
             this->simTime_sec+newDetectEventCount*this->detectDuration_sec
            );
          } //else {
            //this->logEvent(
            // "jetson-"+std::to_string(this->workerId)+"-detect-gtf-"+
            // std::to_string(this->claimedJobs.front()->getJobId()),
            // this->simTime_sec+newDetectEventCount*this->detectDuration_sec
            //);
          //}
          this->detectTime_sec -= this->detectDuration_sec;
          newDetectEventCount += 1;
        }
        // if this->claimedJobs.size() == 0, transition to IDLE
        if(this->claimedJobs.size()==0) {
          this->detectTime_sec = 0.0;
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-detect-stop",
           this->simTime_sec+sanitizedSeconds
          );
          this->logEvent(
           "jetson-"+std::to_string(this->workerId)+"-idle-start",
           this->simTime_sec+sanitizedSeconds
          );
          setPowerState(JetsonTX2::PowerState::IDLE);
        }
      }
    }
    // Update simulation time
    this->simTime_sec += sanitizedSeconds;
  }

  double JetsonTX2::getWatt(const JetsonTX2::PowerState& powerState) const {
    double watt = 0.0;
    switch(powerState) {
      case JetsonTX2::PowerState::OFF:
        watt = 0.0;
        break;
      case JetsonTX2::PowerState::SLEEP:
        watt = 0.5;
        break;
      case JetsonTX2::PowerState::IDLE:
        watt = 0.5;
        break;
      case JetsonTX2::PowerState::DETECT:
        watt = 11.3272;
        break;
      default:
        watt = 0.0;
        break;
    }
    return watt;
  }

  void JetsonTX2::setPowerState(const PowerState& powerState) {
    this->powerState = powerState;
    this->setPower(getWatt(this->powerState));
  }
}
