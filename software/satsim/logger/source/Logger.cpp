// Logger.cpp
// Logger class implementation file
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

// Standard library
#include <fstream>    // ofstream
#include <string>     // string
#include <utility>    // pair
#include <vector>     // vector

// satsim
#include <Logger.hpp> // Logger

namespace satsim {
  Logger::Logger(const std::string& timeUnits) : timeUnits(timeUnits) {}

  void Logger::logEvent(const std::string& name, const double& time) {
    if(this->eventLogs.count(name)==0) {
      this->eventLogs[name] = std::vector<double>();
    }
    this->eventLogs[name].push_back(time);
  }

  void Logger::logMeasurement(
   const std::string& name, const double& time, const double& measurement
  ) {
    if(this->measurementLogs.count(name)==0) {
      this->measurementLogs[name] = std::vector< std::pair<double,double> >();
    }
    this->measurementLogs[name].push_back(
     std::pair<double,double>(time,measurement)
    );
  }

  void Logger::exportCsvs(const std::string& pathToDir) {
    // sanitize pathToDir
    std::string sanitizedPathToDir(pathToDir);
    if(sanitizedPathToDir.back()!='/') {
      sanitizedPathToDir.push_back('/');
    }
    // for each event, write a csv file
    for(const auto& e : this->eventLogs) {
      std::ofstream outFile;
      outFile.open(sanitizedPathToDir+"event-"+e.first+".csv");
      outFile << e.first << " time (" << this->timeUnits << "),"
              << std::endl;
      for(size_t i=0; i<e.second.size(); i++) {
        outFile << e.second.at(i) << ","
                << std::endl;
      }
      outFile.close();
    }
    // for each measurement, write a csv file
    for(const auto& e : this->measurementLogs) {
      std::ofstream outFile;
      outFile.open(sanitizedPathToDir+"measurement-"+e.first+".csv");
      outFile << "Time (" << this->timeUnits << ")," << e.first << ","
              << std::endl;
      for(size_t i=0; i<e.second.size(); i++) {
        outFile << e.second.at(i).first << "," << e.second.at(i).second << ","
                << std::endl;
      }
      outFile.close();
    }
  }
}
