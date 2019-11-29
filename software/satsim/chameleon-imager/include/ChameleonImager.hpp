// ChameleonImager.hpp
// Chameleon Imager class header file
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
