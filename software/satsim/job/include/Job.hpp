// Job.hpp
// Job class header file
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

#ifndef SATSIM_JOB_HPP
#define SATSIM_JOB_HPP

// Standard library
#include <cstddef>    // size_t
#include <map>        // map
#include <string>     // string

// satsim
#include <ILog.hpp>   // Logger interface
#include <ISim.hpp>   // Simulator interface
#include <Logger.hpp> // Logger

namespace satsim {
  class Job: public ILog, public ISim {
  public:
    Job(const size_t& id, const size_t& taskCount, Logger* logger=NULL);
    Job(const Job& job) = default;
    Job(Job&& job) = default;
    virtual ~Job() = default;
    virtual Job& operator=(const Job& job) = default;
    virtual Job& operator=(Job&& job) = default;
    virtual Job* clone() const;
    size_t getJobId() const;
    size_t getUnclaimedTaskCount() const;
    void claimTasks(const size_t& workerId, const size_t& count);
    void unclaimTasks(const size_t& workerId);
    size_t getClaimedTaskCount(const size_t& workerId) const;
    size_t getWorkerTaskCount(const size_t& workerId) const;
    void completeTask(const size_t& workerId);
    virtual void logEvent(const std::string& name, const double& time);
    virtual void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    virtual void update(const double& seconds);
  private:
    size_t id;
    size_t unclaimedTasks;
    std::map<size_t,size_t> workerIdToClaimedTaskCount;
    std::map<size_t,size_t> workerIdToCompletedTaskCount;
    Logger* logger; // singleton, should not be deleted
  };
}

#endif
