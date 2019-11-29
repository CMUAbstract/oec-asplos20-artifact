// Logger.hpp
// Logger class header file
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

#ifndef SATSIM_LOGGER_HPP
#define SATSIM_LOGGER_HPP

// Standard library
#include <map>     // map
#include <string>  // string
#include <utility> // pair
#include <vector>  // vector

namespace satsim {
  class Logger {
  public:
    Logger(const std::string& timeUnits);
    void logEvent(const std::string& name, const double& time);
    void logMeasurement(
     const std::string& name, const double& time, const double& measurement
    );
    void exportCsvs(const std::string& pathToDir);
  private:
    std::string timeUnits;
    std::map<std::string,std::vector<double>> eventLogs;
    std::map<std::string,std::vector<std::pair<double,double>>> measurementLogs;
  };
}

#endif
