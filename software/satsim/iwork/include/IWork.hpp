// IWork.hpp
// IWork interace file
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

#ifndef SATSIM_IWORK_HPP
#define SATSIM_IWORK_HPP

// Standard library
#include <cstddef> // size_t
#include <deque>   // deque

// satsim
#include <Job.hpp> // Job

namespace satsim {
  class IWork {
  public:
    virtual size_t getWorkerId() const = 0;
    virtual void setWorkerId(const size_t& id) = 0;
    virtual size_t getClaimedJobCount() const = 0;
    virtual std::deque<Job*> getClaimedJobs() = 0;
    virtual void addClaimedJob(Job* job) = 0;
    virtual size_t getCompletedJobCount() const = 0;
    virtual std::deque<Job*> getCompletedJobs() = 0;
  };
}

#endif
