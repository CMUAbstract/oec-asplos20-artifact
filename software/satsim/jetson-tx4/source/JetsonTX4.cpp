// JetsonTX4.cpp
// Jetson TX4 class implementation file
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
#include <algorithm>          // max
#include <cstddef>            // size_t

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <JetsonTX4.hpp>      // JetsonTX4
#include <Logger.hpp>         // Logger

namespace satsim {
  const double JetsonTX4::detectDuration_sec = 0.044860/2.0; // Seconds per detect

  JetsonTX4::JetsonTX4(
   const double& initialVoltage_V, const PowerState& initialPowerState,
   Logger* logger
  ) : EnergyConsumer(initialVoltage_V, 0.0, logger),
      powerState(initialPowerState), simTime_sec(0.0), detectTime_sec(0.0),
      workerId(0), beginFlag(true) {
    this->setPower(getWatt(this->powerState));
  }

  JetsonTX4* JetsonTX4::clone() const {
    return new JetsonTX4(*this);
  }

  double JetsonTX4::getSimTime() const {
    return this->simTime_sec;
  }

  void JetsonTX4::setSimTime(const double& seconds) {
    this->simTime_sec = std::max(0.0,seconds);
  }

  size_t JetsonTX4::getWorkerId() const {
    return this->workerId;
  }

  void JetsonTX4::setWorkerId(const size_t& id) {
    this->workerId = id;
  }

  size_t JetsonTX4::getClaimedJobCount() const {
    return this->claimedJobs.size();
  }

  std::deque<Job*> JetsonTX4::getClaimedJobs() {
    return claimedJobs;
  }

  void JetsonTX4::addClaimedJob(Job* job) {
    this->claimedJobs.push_back(job);
  }

  size_t JetsonTX4::getCompletedJobCount() const {
    return this->completedJobs.size();
  }

  std::deque<Job*> JetsonTX4::getCompletedJobs() {
    return this->completedJobs;
  }

  bool JetsonTX4::isIdle() const {
    if(this->powerState==PowerState::IDLE) {
      return true;
    } else {
      return false;
    }
  }

  void JetsonTX4::update(const double& seconds) {
    // Sanitize input
    double sanitizedSeconds = std::max(0.0,seconds);
    // State machine logic
    // If power state is OFF
    if(this->powerState==JetsonTX4::PowerState::OFF) {
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
          setPowerState(JetsonTX4::PowerState::DETECT);
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
          setPowerState(JetsonTX4::PowerState::IDLE);
        }
      }
    }
    // otherwise if power state is SLEEP
    else if(this->powerState==JetsonTX4::PowerState::SLEEP) {
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
        setPowerState(JetsonTX4::PowerState::OFF);
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
          setPowerState(JetsonTX4::PowerState::DETECT);
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
          setPowerState(JetsonTX4::PowerState::IDLE);
        }
      }
    }
    // otherwise if power state is IDLE
    else if(this->powerState==JetsonTX4::PowerState::IDLE) {
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
        setPowerState(JetsonTX4::PowerState::OFF);
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
        setPowerState(JetsonTX4::PowerState::SLEEP);
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
        setPowerState(JetsonTX4::PowerState::DETECT);
      }
    }
    // otherwise if power state is DETECT
    else if(this->powerState==JetsonTX4::PowerState::DETECT) {
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
        setPowerState(JetsonTX4::PowerState::OFF);
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
        setPowerState(JetsonTX4::PowerState::SLEEP);
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
          setPowerState(JetsonTX4::PowerState::IDLE);
        }
      }
    }
    // Update simulation time
    this->simTime_sec += sanitizedSeconds;
  }

  double JetsonTX4::getWatt(const JetsonTX4::PowerState& powerState) const {
    double watt = 0.0;
    switch(powerState) {
      case JetsonTX4::PowerState::OFF:
        watt = 0.0;
        break;
      case JetsonTX4::PowerState::SLEEP:
        watt = 0.5;
        break;
      case JetsonTX4::PowerState::IDLE:
        watt = 0.5;
        break;
      case JetsonTX4::PowerState::DETECT:
        watt = 2.0*11.3272;
        break;
      default:
        watt = 0.0;
        break;
    }
    return watt;
  }

  void JetsonTX4::setPowerState(const PowerState& powerState) {
    this->powerState = powerState;
    this->setPower(getWatt(this->powerState));
  }
}
