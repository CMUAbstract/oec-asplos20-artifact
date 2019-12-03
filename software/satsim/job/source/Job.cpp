// Job.cpp
// Job class implementation file
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
#include <algorithm>  // max
#include <string>     // string

// satsim
#include <Logger.hpp> // Logger
#include <Job.hpp>    // Job

namespace satsim {
  Job::Job(const size_t& id, const size_t& taskCount, Logger* logger) :
   id(id), unclaimedTasks(taskCount), logger(logger) {}

  Job* Job::clone() const {
    return new Job(*this);
  }

  size_t Job::getJobId() const {
    return this->id;
  }

  size_t Job::getUnclaimedTaskCount() const {
    return this->unclaimedTasks;
  }

  void Job::claimTasks(const size_t& workerId, const size_t& count) {
    if(this->workerIdToClaimedTaskCount.count(workerId)==0) {
      this->workerIdToClaimedTaskCount[workerId] = 0;
    }
    if(this->unclaimedTasks<count) {
      this->workerIdToClaimedTaskCount[workerId] += this->unclaimedTasks;
      this->unclaimedTasks = 0;
    } else {
      this->unclaimedTasks -= count;
      this->workerIdToClaimedTaskCount[workerId] += count;
    }
  }

  void Job::unclaimTasks(const size_t& workerId) {
    if(this->workerIdToClaimedTaskCount.count(workerId)!=0) {
      this->unclaimedTasks += this->workerIdToClaimedTaskCount[workerId];
      this->workerIdToClaimedTaskCount[workerId] = 0;
    }
  }

  size_t Job::getClaimedTaskCount(const size_t& workerId) const {
    if(this->workerIdToClaimedTaskCount.count(workerId)!=0) {
      return this->workerIdToClaimedTaskCount.at(workerId);
    } else {
      return 0;
    }
  }

  size_t Job::getWorkerTaskCount(const size_t& workerId) const {
    size_t total = 0;
    if(this->workerIdToClaimedTaskCount.count(workerId)!=0) {
      total += this->workerIdToClaimedTaskCount.at(workerId);
    }
    if(this->workerIdToCompletedTaskCount.count(workerId)!=0) {
      total += this->workerIdToCompletedTaskCount.at(workerId);
    }
    return total;
  }

  void Job::completeTask(const size_t& workerId) {
    if(this->workerIdToClaimedTaskCount.count(workerId)!=0) {
      if(this->workerIdToCompletedTaskCount.count(workerId)==0) {
        this->workerIdToCompletedTaskCount[workerId] = 0;
      }
      this->workerIdToClaimedTaskCount[workerId]   -= 1;
      this->workerIdToCompletedTaskCount[workerId] += 1;
    }
  }

  void Job::logEvent(const std::string& name, const double& time) {
    if(this->logger!=NULL) {
      this->logger->logEvent(name, time);
    }
  }

  void Job::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->logger!=NULL) {
      this->logger->logMeasurement(name, time, measurement);
    }
  }

  void Job::update(const double& seconds) {}
}
