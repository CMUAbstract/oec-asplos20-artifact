// JetsonTX4.hpp
// Jetson TX4 class header file
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

#ifndef SATSIM_JETSON_TX4_HPP
#define SATSIM_JETSON_TX4_HPP

// Standard library
#include <cstddef>            // size_t
#include <deque>              // deque

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <IWork.hpp>          // IWork
#include <Logger.hpp>         // Logger

namespace satsim {
  class JetsonTX4: public EnergyConsumer, public IWork {
  public:
    enum class PowerState: uint8_t {
      OFF    = 0,
      SLEEP  = 1,
      IDLE   = 2,
      DETECT = 3
    };
    JetsonTX4(
     const double& initialVoltage_V, const PowerState& initialPowerState,
     Logger* logger=NULL
    );
    JetsonTX4(const JetsonTX4& jetsonTX4) = default;
    JetsonTX4(JetsonTX4&& jetsonTX4) = default;
    virtual ~JetsonTX4() = default;
    virtual JetsonTX4& operator=(const JetsonTX4& jetsonTX4) = default;
    virtual JetsonTX4& operator=(JetsonTX4&& jetsonTX4) = default;
    virtual JetsonTX4* clone() const;
    double getSimTime() const;
    void setSimTime(const double& seconds);
    size_t getWorkerId() const;
    void setWorkerId(const size_t& id);
    size_t getClaimedJobCount() const;
    std::deque<Job*> getClaimedJobs();
    void addClaimedJob(Job* job);
    size_t getCompletedJobCount() const;
    std::deque<Job*> getCompletedJobs();
    bool isIdle() const;
    virtual void update(const double& seconds);
  private:
    static const double detectDuration_sec; // Seconds per detect
    PowerState powerState;                  // Power state
    double simTime_sec;                     // Simulation time
    double detectTime_sec;                  // Time spent on current detect task
    size_t workerId;
    bool beginFlag;
    std::deque<Job*> claimedJobs;
    std::deque<Job*> completedJobs;
    double getWatt(const PowerState& powerState) const;
    void setPowerState(const PowerState& powerState);
  };
}

#endif
