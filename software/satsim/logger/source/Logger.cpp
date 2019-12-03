// Logger.cpp
// Logger class implementation file
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
