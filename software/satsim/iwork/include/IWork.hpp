// IWork.hpp
// IWork interace file
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
