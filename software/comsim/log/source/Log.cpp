// Log.cpp
// Log class implementation file
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
#include <cstddef>      // size_t
#include <cstdint>      // uint8_t
#include <fstream>      // ofstream
#include <string>       // string
#include <utility>      // pair
#include <vector>       // vector

// comsim
#include <Log.hpp>      // Log
#include <LogLevel.hpp> // LogLevel

namespace comsim {
  Log::Log(const std::vector<LogLevel>& levels, const std::string& dir) {
    // ingest log levels
    this->levels = static_cast<uint8_t>(0);
    for(size_t i=0; i<levels.size(); i++) {
      this->levels |= static_cast<uint8_t>(levels.at(i));
    }
    // sanitize path to dir
    std::string sanitized_dir(dir);
    if(sanitized_dir.back()!='/') {
      sanitized_dir.push_back('/');
    }
    this->dir = sanitized_dir;
  }

  void Log::evnt(
   const LogLevel& level, const std::string& dateTime, const std::string& evnt
  ) {
    if(isEnabled(level)) {
      if(this->evntLogs.count(evnt)==0) {
        this->evntLogs[evnt] = std::vector<std::string>();
        std::ofstream outFile(this->dir+"evnt-"+evnt+".csv",std::ios::out);
        outFile << evnt << "-time,"
                << std::endl;
        outFile.close();
      }
      this->evntLogs[evnt].push_back(dateTime);
      if(this->evntLogs[evnt].size()>=BUFFER_SIZE) {
        this->writeEvnt(evnt);
        this->evntLogs[evnt].clear();
      }
    }
  }

  void Log::meas(
   const LogLevel& level, const std::string& dateTime,
   const std::string& meas, const std::string& valu
  ) {
    if(isEnabled(level)) {
      if(this->measLogs.count(meas)==0) {
        this->measLogs[meas] =
         std::vector< std::pair<std::string,std::string> >();
        std::ofstream outFile(this->dir+"meas-"+meas+".csv",std::ios::out);
        outFile << "time," << meas << ","
                << std::endl;
        outFile.close();
      }
      this->measLogs[meas].push_back(
       std::pair<std::string,std::string>(dateTime,valu)
      );
      if(this->measLogs[meas].size()>=BUFFER_SIZE) {
        this->writeMeas(meas);
        this->measLogs[meas].clear();
      }
    }
  }

  void Log::writeAll() const {
    for(const auto& e : this->evntLogs) {
      this->writeEvnt(e.first);
    }
    for(const auto& e : this->measLogs) {
      this->writeMeas(e.first);
    }
  }

  bool Log::isEnabled(const LogLevel& level) const {
    return this->levels&static_cast<uint8_t>(level);
  }

  void Log::writeEvnt(const std::string& evnt) const {
    std::ofstream outFile(this->dir+"evnt-"+evnt+".csv",std::ios::app);
    for(size_t i=0; i<this->evntLogs.at(evnt).size(); i++) {
      outFile << this->evntLogs.at(evnt).at(i) << ","
              << std::endl;
    }
    outFile.close();
  }

  void Log::writeMeas(const std::string& meas) const {
    std::ofstream outFile(this->dir+"meas-"+meas+".csv",std::ios::app);
    for(size_t i=0; i<this->measLogs.at(meas).size(); i++) {
      outFile << this->measLogs.at(meas).at(i).first << ","
              << this->measLogs.at(meas).at(i).second << ","
              << std::endl;
    }
    outFile.close();
  }
}
