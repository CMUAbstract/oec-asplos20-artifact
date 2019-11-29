// JetsonTX2.hpp
// Jetson TX2 class header file
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

#ifndef SATSIM_JETSON_TX2_HPP
#define SATSIM_JETSON_TX2_HPP

// Standard library
#include <cstddef>            // size_t
#include <deque>              // deque

// satsim
#include <EnergyConsumer.hpp> // EnergyConsumer
#include <IWork.hpp>          // IWork
#include <Logger.hpp>         // Logger

namespace satsim {
  class JetsonTX2: public EnergyConsumer, public IWork {
  public:
    enum class PowerState: uint8_t {
      OFF    = 0,
      SLEEP  = 1,
      IDLE   = 2,
      DETECT = 3
    };
    JetsonTX2(
     const double& initialVoltage_V, const PowerState& initialPowerState,
     Logger* logger=NULL
    );
    JetsonTX2(const JetsonTX2& jetsonTX2) = default;
    JetsonTX2(JetsonTX2&& jetsonTX2) = default;
    virtual ~JetsonTX2() = default;
    virtual JetsonTX2& operator=(const JetsonTX2& jetsonTX2) = default;
    virtual JetsonTX2& operator=(JetsonTX2&& jetsonTX2) = default;
    virtual JetsonTX2* clone() const;
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
