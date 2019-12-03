// test-ground-station.cpp
// GroundStation class test file
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
#include <array>             // array
#include <cstdlib>           // exit, EXIT_SUCCESS
#include <string>            // to_string

#include <iomanip>       // setprecision
#include <ios>           // fixed, showpoint
#include <iostream>      // cout
#include <ostream>       // endl

// satsim
#include <constants.hpp>     // constants
#include <DateTime.hpp>      // DateTime
#include <GroundStation.hpp> // GroundStation
#include <Log.hpp>           // Log
#include <LogLevel.hpp>      // LogLevel
#include <utilities.hpp>     // utilities

int main(int argc, char** argv) {
  // Setup
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::INFO};
  comsim::Log log(levels,"../test");
  // Example 1
  comsim::DateTime dt1(1995,10, 1, 0, 0, 0,0);
  comsim::GroundStation gs1(40.0,-75.0,0.025,&dt1,1,&log);
  const double JD1 = comsim::util::calcJulianDayFromYMD(
   dt1.getYear(), dt1.getMonth(), dt1.getDay()
  );
  const uint32_t SEC1 = comsim::util::calcSecSinceMidnight(
   dt1.getHour(), dt1.getMinute(), dt1.getSecond()
  );
  const uint32_t NS1 = dt1.getNanosecond();
  log.meas(
   comsim::LogLevel::INFO, dt1.toString(), "zrot", std::to_string(
    comsim::util::calcGMSTRadFromUT1(JD1,SEC1,NS1)/comsim::cnst::RAD_PER_DEG
   ) // expected value: 9.257
  );
  // Example 2
  comsim::DateTime dt2(1995,10, 1, 9, 0, 0,0);
  comsim::GroundStation gs2(40.0,-75.0,0.0,&dt2,2,&log);
  const double JD2 = comsim::util::calcJulianDayFromYMD(
   dt2.getYear(), dt2.getMonth(), dt2.getDay()
  );
  const uint32_t SEC2 = comsim::util::calcSecSinceMidnight(
   dt2.getHour(), dt2.getMinute(), dt2.getSecond()
  );
  const uint32_t NS2 = dt2.getNanosecond();
  log.meas(
   comsim::LogLevel::INFO, dt2.toString(), "zrot", std::to_string(
    comsim::util::calcGMSTRadFromUT1(JD2,SEC2,NS2)/comsim::cnst::RAD_PER_DEG
   ) // expected value: 144.627
  );
  std::array<double,3> gs2Posn = gs2.getECIPosn();
  log.meas(
   comsim::LogLevel::INFO, dt2.toString(), "x-km", std::to_string(gs2Posn.at(0))
  ); // expected value: 1703.295
  log.meas(
   comsim::LogLevel::INFO, dt2.toString(), "y-km", std::to_string(gs2Posn.at(1))
  ); // expected value: 4586.650
  log.meas(
   comsim::LogLevel::INFO, dt2.toString(), "z-km", std::to_string(gs2Posn.at(2))
  ); // expected value: 4077.984
  // Example 3
  comsim::DateTime dt3(1995,11,18,12,46, 0,0);
  comsim::GroundStation gs3(45.0,-93.0,0.0,&dt3,3,&log);
  const double JD3 = comsim::util::calcJulianDayFromYMD(
   dt3.getYear(), dt3.getMonth(), dt3.getDay()
  );
  const uint32_t SEC3 = comsim::util::calcSecSinceMidnight(
   dt3.getHour(), dt3.getMinute(), dt3.getSecond()
  );
  const uint32_t NS3 = dt3.getNanosecond();
  //std::array<double,3> gs3Posn = gs3.getECIPosn();
  std::array<double,3> satPosn = {-4400.594,1932.870,4760.712};
  log.meas(
   comsim::LogLevel::INFO, dt3.toString(), "el-deg",
   std::to_string(comsim::util::calcElevationDeg(
    JD3,SEC3,NS3,gs3.getLatitude(),gs3.getLongitude(),gs3.getHAE(),satPosn
   ))
  ); // expected value: 81.52
  // Write logs*/
  log.writeAll();
  std::exit(EXIT_SUCCESS);
}
