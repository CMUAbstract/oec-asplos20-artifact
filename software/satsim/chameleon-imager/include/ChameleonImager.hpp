// ChameleonImager.hpp
// Chameleon Imager class header file
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

#ifndef SATSIM_CHAMELEON_IMAGER_HPP
#define SATSIM_CHAMELEON_IMAGER_HPP

// Standard library
#include <cstddef>            // size_t
#include <deque>              // deque

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <IWork.hpp>          // IWork
#include <Logger.hpp>         // Logger

namespace satsim {
  class ChameleonImager: public EnergyConsumer, public IWork {
  public:
    enum class PowerState: uint8_t {
      OFF     = 0,
      IDLE    = 1,
      IMAGING = 2,
      READOUT = 3
    };
    ChameleonImager(
     const double& initialVoltage_V, const PowerState& initialPowerState,
     Logger* logger=NULL
    );
    ChameleonImager(const ChameleonImager& chameleonImager) = default;
    ChameleonImager(ChameleonImager&& chameleonImager) = default;
    virtual ~ChameleonImager() = default;
    virtual ChameleonImager& operator=(const ChameleonImager& chameleonImager) = default;
    virtual ChameleonImager& operator=(ChameleonImager&& chameleonImager) = default;
    virtual ChameleonImager* clone() const;
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
    bool hasImage() const;
    Job* dequeImage();
    virtual void update(const double& seconds);
  private:
    static const double imagingDuration_sec;
    static const double readoutDuration_sec;
    PowerState powerState;
    double simTime_sec;
    double imagingTime_sec;
    double readoutTime_sec;
    size_t workerId;
    std::deque<Job*> imagingFifo;
    std::deque<Job*> readoutFifo;
    std::deque<Job*> readyImages;
    double getWatt(const PowerState& powerState) const;
    void setPowerState(const PowerState& powerState);
  };
}

#endif
