// ILog.hpp
// ILog interace file
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

#ifndef SATSIM_ILOG_HPP
#define SATSIM_ILOG_HPP

// Standard library
#include <string> // string

namespace satsim {
  class ILog {
  public:
    virtual void logEvent(const std::string& name, const double& time) = 0;
    virtual void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    ) = 0;
  };
}

#endif
