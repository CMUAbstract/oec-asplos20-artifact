// close-spaced.cpp
// Simulates a satellite constellation and ground station system with sensors.
// Satellite configuration files should produce a close-spaced formation.
// Requires C++17 (e.g. GCC 8) for std::filesystem
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
#include <algorithm>         // sort
#include <cmath>             // round
#include <cstdlib>           // exit, EXIT_SUCCESS
#include <filesystem>        // path
#include <fstream>           // ifstream
#include <iostream>          // cout
#include <map>               // map
#include <ostream>           // endl
#include <vector>            // vector

// comsim
#include <constants.hpp>     // constants
#include <Channel.hpp>       // Channel
#include <DateTime.hpp>      // DateTime
#include <GroundStation.hpp> // GroundStation
#include <Log.hpp>           // Log
#include <LogLevel.hpp>      // LogLevel
#include <Transmit.hpp>      // Transmit
#include <Satellite.hpp>     // Satellite
#include <Sensor.hpp>        // Sensor
#include <Receive.hpp>       // Receive
#include <utilities.hpp>     // utilities

int main(int argc, char** argv) {
  // Set up variables
  std::filesystem::path logDirectory;            // path to log destination
  std::filesystem::path dateTimeFile;            // file specifying date & time
  std::filesystem::path satelliteFile;           // satellite TLE file
  std::filesystem::path constellationFile;       // constellation configuration
  std::filesystem::path sensorFile;              // file specifying sensor
  std::vector<std::filesystem::path> gndFiles;   // list of (lat,lon,h) files
  std::filesystem::path txSatFile;               // satellite TX configuration
  std::vector<std::filesystem::path> txGndFiles; // list of ground station TX
  std::filesystem::path rxSatFile;               // satellite RX configuration
  std::vector<std::filesystem::path> rxGndFiles; // list of ground station RX
  // Parse command line argument(s)
  if(argc!=10) {
    std::cout << "Usage: " << argv[0]
              << " /path/to/logs/dst/"
              << " /path/to/dt/"
              << " /path/to/sat/"
              << " /path/to/sensor/"
              << " /path/to/gnd/"
              << " /path/to/tx-sat/"
              << " /path/to/tx-gnd/"
              << " /path/to/rx-sat/"
              << " /path/to/rx-gnd/"
              << std::endl;
    std::exit(EXIT_SUCCESS);
  } else {
    // Get date-time file path
    logDirectory = std::filesystem::path(argv[1]);
    // Get date-time file path
    std::filesystem::path dtdir(argv[2]);
    std::filesystem::directory_iterator it(dtdir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        dateTimeFile = it->path();
      }
      it++;
    }
    // Get satellite file path, constellation file path
    std::filesystem::path tledir(argv[3]);
    it = std::filesystem::directory_iterator(tledir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".tle") {
        satelliteFile = it->path();
      } else if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        constellationFile = it->path();
      }
      it++;
    }
    // Get sensor file path
    std::filesystem::path sensordir(argv[4]);
    it = std::filesystem::directory_iterator(sensordir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        sensorFile = it->path();
      }
      it++;
    }
    // Get ground station file paths
    std::filesystem::path llhdir(argv[5]);
    it = std::filesystem::directory_iterator(llhdir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        gndFiles.push_back(it->path());
      }
      it++;
    }
    // Get satellite TX file path
    std::filesystem::path sattxdir(argv[6]);
    it = std::filesystem::directory_iterator(sattxdir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        txSatFile = it->path();
      }
      it++;
    }
    // Get ground station TX file paths
    std::filesystem::path gndtxdir(argv[7]);
    it = std::filesystem::directory_iterator(gndtxdir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        txGndFiles.push_back(it->path());
      }
      it++;
    }
    // Get satellite RX file path
    std::filesystem::path satrxdir(argv[8]);
    it = std::filesystem::directory_iterator(satrxdir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        rxSatFile = it->path();
      }
      it++;
    }
    // Get ground station RX file paths
    std::filesystem::path gndrxdir(argv[9]);
    it = std::filesystem::directory_iterator(gndrxdir);
    while(it!=std::filesystem::end(it)) {
      std::string pathStr = it->path().string();
      if(pathStr.substr(pathStr.size()-4,4)==".dat") {
        rxGndFiles.push_back(it->path());
      }
      it++;
    }
  }
  // Set up log
  std::vector<comsim::LogLevel> levels = {comsim::LogLevel::INFO};
  comsim::Log log(levels,logDirectory.string());
  // Set up date and time
  std::ifstream dateTimeHandle(dateTimeFile.string());
  std::string line = "";
  std::getline(dateTimeHandle,line); // Read header
  std::getline(dateTimeHandle,line); // Read values
  dateTimeHandle.close();
  int16_t year = static_cast<int16_t>(std::stoi(line.substr(0,4)));
  uint8_t month = static_cast<uint8_t>(std::stoi(line.substr(5,2)));
  uint8_t day = static_cast<uint8_t>(std::stoi(line.substr(8,2)));
  uint8_t hour = static_cast<uint8_t>(std::stoi(line.substr(11,2)));
  uint8_t minute = static_cast<uint8_t>(std::stoi(line.substr(14,2)));
  uint8_t second = static_cast<uint8_t>(std::stoi(line.substr(17,2)));
  uint32_t nanosecond = static_cast<uint32_t>(std::stoi(line.substr(20,9)));
  comsim::DateTime dateTime(year,month,day,hour,minute,second,nanosecond);
  // Set up constellation configuration parameters
  std::ifstream constellationHandle(constellationFile.string());
  line = "";
  std::getline(constellationHandle,line); // Read header
  std::getline(constellationHandle,line); // Read values
  constellationHandle.close();
  uint16_t count = static_cast<uint16_t>(std::stoi(line.substr(0,5)));
  uint8_t hourStep = static_cast<uint8_t>(std::stoi(line.substr(6,2)));
  uint8_t minuteStep = static_cast<uint8_t>(std::stoi(line.substr(9,2)));
  uint8_t secondStep = static_cast<uint8_t>(std::stoi(line.substr(12,2)));
  uint32_t nanosecondStep = static_cast<uint32_t>(std::stoi(line.substr(15,9)));
  // Set up satellites
  comsim::DateTime localTime = dateTime;
  std::vector<comsim::Satellite> satellites;
  for(size_t i=count; i!=0; i--) {
    satellites.push_back(
     comsim::Satellite(satelliteFile.string(),&dateTime,&log)
    );
    uint32_t id = satellites.back().getCatalogNumber();
    satellites.back().setCatalogNumber(1000*id+(i-1));
    satellites.back().setLocalTime(localTime);
    localTime.update(hourStep,minuteStep,secondStep,nanosecondStep);
  }
  std::sort(
   satellites.begin(), satellites.end(),
   [](const comsim::Satellite& s1, const comsim::Satellite& s2) {
    return s1.getCatalogNumber() < s2.getCatalogNumber();
   }
  );
  // Set up satellite sensors
  std::ifstream sensorHandle(sensorFile.string());
  line = "";
  std::getline(sensorHandle,line); // Read header
  std::getline(sensorHandle,line); // Read value(s)
  sensorHandle.close();
  uint64_t bitsPerSense = static_cast<uint64_t>(std::stoll(line.substr(0,10)));
  uint32_t pixelCount = static_cast<uint32_t>(std::stoi(line.substr(11,5)));
  double pixelSizeM = static_cast<double>(std::stod(line.substr(17,11)));
  double focalLengthM = static_cast<double>(std::stod(line.substr(29,10)));
  const double threshCoeff =
   (static_cast<double>(pixelCount)*pixelSizeM/focalLengthM);
  std::map<uint32_t,comsim::Sensor*> satId2Sensor;
  for(size_t i=0; i<satellites.size(); i++) {
    uint32_t id = satellites.at(i).getCatalogNumber();
    satId2Sensor[id] = new comsim::Sensor(&dateTime,id,&log);
    satId2Sensor[id]->setBitsPerSense(static_cast<uint64_t>(std::round(
     static_cast<double>(bitsPerSense)/static_cast<double>(satellites.size())
    )));
    satId2Sensor[id]->setPrevSensePosn(satellites.at(i).getECIPosn());
    satId2Sensor[id]->setPrevSenseDateTime(dateTime);
    satId2Sensor[id]->setECIPosn(satellites.at(i).getECIPosn());
  }
  // Set up ground stations
  std::vector<comsim::GroundStation> groundStations;
  for(size_t i=0; i<gndFiles.size(); i++) {
    std::ifstream gndHandle(gndFiles.at(i).string());
    line = "";
    std::getline(gndHandle,line); // Read header
    std::getline(gndHandle,line); // Read values
    gndHandle.close();
    uint32_t id  = static_cast<uint32_t>(std::stoi(line.substr(0,10)));
    double   lat = std::stod(line.substr(11,13));
    double   lon = std::stod(line.substr(25,14));
    double   hae = std::stod(line.substr(40,13));
    groundStations.push_back(
     comsim::GroundStation(lat,lon,hae,&dateTime,id,&log)
    );
  }
  std::sort(
   groundStations.begin(), groundStations.end(),
   [](const comsim::GroundStation& g1, const comsim::GroundStation& g2) {
    return g1.getID() < g2.getID();
   }
  );
  // Set up satellite TX
  std::map<uint32_t,comsim::Transmit*> satId2Tx;
  for(size_t i=0; i<satellites.size(); i++) {
    std::ifstream satTxHandle(txSatFile.string());
    line = "";
    std::getline(satTxHandle,line); // Read header
    std::getline(satTxHandle,line); // Read values
    satTxHandle.close();
    uint32_t id = satellites.at(i).getCatalogNumber();
    std::array<double,3> posn = satellites.at(i).getECIPosn();
    double powerW = std::stod(line.substr(11,16));
    double lineLossDB = std::stod(line.substr(28,13));
    double gainDB = std::stod(line.substr(42,13));
    double centerFrequencyHz = std::stod(line.substr(56,22));
    double bandwidthHz = std::stod(line.substr(79,23));
    satId2Tx[id] =
     new comsim::Transmit(posn,powerW,lineLossDB,gainDB,&dateTime,id,&log);
  }
  // Set up ground station TX
  std::map<uint32_t,comsim::Transmit*> gndId2Tx;
  for(size_t i=0; i<txGndFiles.size(); i++) {
    std::ifstream gndTxHandle(txGndFiles.at(i).string());
    line = "";
    std::getline(gndTxHandle,line); // Read header
    std::getline(gndTxHandle,line); // Read values
    gndTxHandle.close();
    uint32_t id = static_cast<uint32_t>(std::stoi(line.substr(0,10)));
    std::array<double,3> posn = {0.0,0.0,0.0};
    for(size_t i=0; i<groundStations.size(); i++) {
      if(groundStations.at(i).getID()==id) {
        posn = groundStations.at(i).getECIPosn();
      }
    }
    double powerW = std::stod(line.substr(11,16));
    double lineLossDB = std::stod(line.substr(28,13));
    double gainDB = std::stod(line.substr(42,13));
    double centerFrequencyHz = std::stod(line.substr(56,22));
    double bandwidthHz = std::stod(line.substr(79,23));
    gndId2Tx[id] =
     new comsim::Transmit(posn,powerW,lineLossDB,gainDB,&dateTime,id,&log);
  }
  // Set up satellite RX
  std::map<uint32_t,comsim::Receive*> satId2Rx;
  for(size_t i=0; i<satellites.size(); i++) {
    std::ifstream satRxHandle(rxSatFile.string());
    line = "";
    std::getline(satRxHandle,line); // Read header
    std::getline(satRxHandle,line); // Read values
    satRxHandle.close();
    uint32_t id = satellites.at(i).getCatalogNumber();
    std::array<double,3> posn = satellites.at(i).getECIPosn();
    double gainDB = std::stod(line.substr(11,13));
    double centerFrequencyHz = std::stod(line.substr(25,22));
    double bandwidthHz = std::stod(line.substr(48,23));
    satId2Rx[id] = new comsim::Receive(posn,gainDB,&dateTime,id,&log);
  }
  // Set up ground station RX
  std::map<uint32_t,comsim::Receive*> gndId2Rx;
  for(size_t i=0; i<rxGndFiles.size(); i++) {
    std::ifstream gndRxHandle(rxGndFiles.at(i).string());
    line = "";
    std::getline(gndRxHandle,line); // Read header
    std::getline(gndRxHandle,line); // Read values
    gndRxHandle.close();
    uint32_t id = static_cast<uint32_t>(std::stoi(line.substr(0,10)));
    std::array<double,3> posn = {0.0,0.0,0.0};
    for(size_t i=0; i<groundStations.size(); i++) {
      if(groundStations.at(i).getID()==id) {
        posn = groundStations.at(i).getECIPosn();
      }
    }
    double gainDB = std::stod(line.substr(11,13));
    double centerFrequencyHz = std::stod(line.substr(25,22));
    double bandwidthHz = std::stod(line.substr(48,23));
    gndId2Rx[id] = new comsim::Receive(posn,gainDB,&dateTime,id,&log);
  }
  // Simulation data
  std::map<uint32_t,bool> satId2Occupied;
  std::map<uint32_t,double> satId2Threshold;
  for(size_t i=0; i<satellites.size(); i++) {
    satId2Occupied[satellites.at(i).getCatalogNumber()] = false;
    satId2Threshold[satellites.at(i).getCatalogNumber()] =
     threshCoeff*comsim::util::calcAltitudeKm(satellites.at(i).getECIPosn());
  }
  std::map<uint32_t,std::vector<comsim::Satellite*>> gndId2VisSats;
  std::map<uint32_t,comsim::Satellite*> gndId2CurrSat;
  for(size_t i=0; i<groundStations.size(); i++) {
    gndId2VisSats[groundStations.at(i).getID()] =
     std::vector<comsim::Satellite*>();
    gndId2CurrSat[groundStations.at(i).getID()] = NULL;
  }
  std::vector<comsim::Channel> downlinks = std::vector<comsim::Channel>();
  std::vector<comsim::Channel> uplinks   = std::vector<comsim::Channel>();
  // Simulation loop
  size_t centisecondCount = 0;
  while(centisecondCount<1080000) { // three hours, i.e. approximately 2 revs
    // Prepare simulation data
    //// Clear active channels
    downlinks.clear();
    uplinks.clear();
    //// Get the current time
    const double JD = comsim::util::calcJulianDayFromYMD(
     dateTime.getYear(),dateTime.getMonth(),dateTime.getDay()
    );
    const uint32_t SEC =
     dateTime.getSecond()+
     static_cast<uint32_t>(dateTime.getMinute())*
     static_cast<uint32_t>(comsim::cnst::SEC_PER_MIN)+
     static_cast<uint32_t>(dateTime.getHour())*
     static_cast<uint32_t>(comsim::cnst::MIN_PER_HOUR)*
     static_cast<uint32_t>(comsim::cnst::SEC_PER_MIN);
    const uint32_t NS = dateTime.getNanosecond();
    //// Determinte visible satellites for each ground station
    //// Clear satellite occupied flag if no longer visible
    for(size_t i=0; i<groundStations.size(); i++) {
      const double LAT      = groundStations.at(i).getLatitude();
      const double LON      = groundStations.at(i).getLongitude();
      const double HAE      = groundStations.at(i).getHAE();
      const uint32_t GND_ID = groundStations.at(i).getID();
      gndId2VisSats[GND_ID].clear();
      bool currSatInView  = false;
      for(size_t j=0; j<satellites.size(); j++) {
        const std::array<double,3> satEciPosn = satellites.at(j).getECIPosn();
        if(
         comsim::util::calcElevationDeg(JD,SEC,NS,LAT,LON,HAE,satEciPosn)>=10.0
        ) {
          gndId2VisSats[GND_ID].push_back(&(satellites.at(j)));
          if(
           gndId2CurrSat[GND_ID]!=NULL &&
           gndId2CurrSat[GND_ID]==&(satellites.at(j))
          ) {
            currSatInView = true;
          }
        }
      }
      if(!currSatInView && gndId2CurrSat[GND_ID]!=NULL) {
        satId2Occupied[gndId2CurrSat[GND_ID]->getCatalogNumber()] = false;
        gndId2CurrSat[GND_ID] = NULL;
      }
    }
    // Simulation logic
    //// For each ground station without a link, connect with the highest sat
    for(size_t i=0; i<groundStations.size(); i++) {
      const uint32_t GND_ID = groundStations.at(i).getID();
      // If no current link, choose the satellite with highest visible elevation
      // and data buffered onboard
      if(gndId2CurrSat[GND_ID]==NULL) {
        const double LAT = groundStations.at(i).getLatitude();
        const double LON = groundStations.at(i).getLongitude();
        const double HAE = groundStations.at(i).getHAE();
        comsim::Satellite* bestSat = NULL;
        uint64_t bestSatBuffer = 0;
        for(size_t j=0; j<satellites.size(); j++) {
          const uint32_t SAT_ID = satellites.at(j).getCatalogNumber();
          const std::array<double,3> satEciPosn = satellites.at(j).getECIPosn();
          const double EL =
           comsim::util::calcElevationDeg(JD,SEC,NS,LAT,LON,HAE,satEciPosn);
          const uint64_t BUF = satId2Sensor[SAT_ID]->getBitsBuffered();
          if(!satId2Occupied[SAT_ID] && EL>=10.0 && BUF>bestSatBuffer) {
            bestSat = &(satellites.at(j));
            bestSatBuffer = BUF;
          }
        }
        if(bestSat!=NULL) {
          satId2Occupied[bestSat->getCatalogNumber()] = true;
          gndId2CurrSat[GND_ID] = bestSat;
        }
        bestSat = NULL;
      }
      // If there are links now, formally construct them
      if(gndId2CurrSat[GND_ID]!=NULL) {
        const uint32_t SAT_ID = gndId2CurrSat[GND_ID]->getCatalogNumber();
        // Construct downlink
        downlinks.push_back(
         comsim::Channel(
          satId2Tx[SAT_ID],gndId2Rx[GND_ID],8.15e9,20.0e6,&dateTime,&log
         )
        );
        // Drain data from satellite to ground station based on time step
        satId2Sensor[SAT_ID]->drainBuffer(static_cast<uint64_t>(// 1 centisecond
         std::round(static_cast<double>(downlinks.back().getBitsPerSec())*0.01)
        ));
        // Construct uplink
        uplinks.push_back(
         comsim::Channel(
          gndId2Tx[GND_ID],satId2Rx[SAT_ID],436.5e6,60.0e3,&dateTime,&log
         )
        );
      }
    }
    //// Sensor data collection logic
    //// For close-spaced, all satellites capture data every frame
    //// So use only the "lead" satellite to check if it is time for a new frame
    const uint32_t LEAD_SAT_ID = satellites.at(0).getCatalogNumber();
    const std::array<double,3> prevSensePosn =
     satId2Sensor[LEAD_SAT_ID]->getPrevSensePosn();
    const comsim::DateTime prevSenseDateTime =
     satId2Sensor[LEAD_SAT_ID]->getPrevSenseDateTime();
    const double PREV_JD = comsim::util::calcJulianDayFromYMD(
     prevSenseDateTime.getYear(), prevSenseDateTime.getMonth(),
     prevSenseDateTime.getDay()
    );
    const uint32_t PREV_SEC =
     prevSenseDateTime.getSecond()+
     static_cast<uint32_t>(prevSenseDateTime.getMinute())*
     static_cast<uint32_t>(comsim::cnst::SEC_PER_MIN)+
     static_cast<uint32_t>(prevSenseDateTime.getHour())*
     static_cast<uint32_t>(comsim::cnst::MIN_PER_HOUR)*
     static_cast<uint32_t>(comsim::cnst::SEC_PER_MIN);
    const uint32_t PREV_NS = prevSenseDateTime.getNanosecond();
    const double PREV_LAT = comsim::util::calcSubpointLatitude(prevSensePosn);
    const double PREV_LON = comsim::util::calcSubpointLongitude(
     PREV_JD, PREV_SEC, PREV_NS, prevSensePosn
    );
    const std::array<double,3> currPosn=satId2Sensor[LEAD_SAT_ID]->getECIPosn();
    const comsim::DateTime currDateTime = dateTime;
    const double CURR_JD = comsim::util::calcJulianDayFromYMD(
     currDateTime.getYear(),currDateTime.getMonth(),currDateTime.getDay()
    );
    const uint32_t CURR_SEC =
     currDateTime.getSecond()+
     static_cast<uint32_t>(currDateTime.getMinute())*
     static_cast<uint32_t>(comsim::cnst::SEC_PER_MIN)+
     static_cast<uint32_t>(currDateTime.getHour())*
     static_cast<uint32_t>(comsim::cnst::MIN_PER_HOUR)*
     static_cast<uint32_t>(comsim::cnst::SEC_PER_MIN);
    const uint32_t CURR_NS = currDateTime.getNanosecond();
    const double CURR_LAT = comsim::util::calcSubpointLatitude(currPosn);
    const double CURR_LON = comsim::util::calcSubpointLongitude(
     CURR_JD, CURR_SEC, CURR_NS, currPosn
    );
    const double distance = comsim::util::calcGreatCircleArc(
     CURR_LON, CURR_LAT, PREV_LON, PREV_LAT
    )*comsim::cnst::WGS_84_A;
    if(distance>=satId2Threshold[LEAD_SAT_ID]) {
      log.evnt(
       comsim::LogLevel::INFO,currDateTime.toString(),"trigger-time"
      );
      for(size_t i=0; i<satellites.size(); i++) {
        satId2Sensor[satellites.at(i).getCatalogNumber()]->triggerSense();
        satId2Threshold[satellites.at(i).getCatalogNumber()] = threshCoeff*
         comsim::util::calcAltitudeKm(satellites.at(i).getECIPosn());
      }
    }
    // Log info once per second
    if(centisecondCount%100==0) {
      if(downlinks.size()==0) {
        log.meas(
         comsim::LogLevel::INFO,
         dateTime.toString(),
         std::string("downlink-Mbps"),
         std::to_string(0.0)
        );
        log.meas(
         comsim::LogLevel::INFO,
         dateTime.toString(),
         std::string("downlink-MB"),
         std::to_string(0.0)
        );
        log.meas(
         comsim::LogLevel::INFO,
         dateTime.toString(),
         std::string("downlink-tx-rx"),
         "None"
        );
      } else {
        for(size_t i=0; i<downlinks.size(); i++) {
          log.meas(
           comsim::LogLevel::INFO,
           dateTime.toString(),
           std::string("downlink-Mbps"),
           std::to_string(
            static_cast<double>(downlinks.at(i).getBitsPerSec())/1.0e6
           )
          );
          log.meas(
           comsim::LogLevel::INFO,
           dateTime.toString(),
           std::string("downlink-MB"),
           std::to_string(
            (1.0*static_cast<double>(downlinks.at(i).getBitsPerSec())/8.0)/1.0e6
           )
          );
          log.meas(
           comsim::LogLevel::INFO,
           dateTime.toString(),
           std::string("downlink-tx-rx"),
           std::to_string(downlinks.at(i).getTransmit()->getID())+"-"+
            std::to_string(downlinks.at(i).getReceive()->getID())
          );
        }
      }
      if(uplinks.size()==0) {
        log.meas(
         comsim::LogLevel::INFO,
         dateTime.toString(),
         std::string("uplink-tx-rx"),
         "None"
        );
      } else {
        for(size_t i=0; i<uplinks.size(); i++) {
          log.meas(
           comsim::LogLevel::INFO,
           dateTime.toString(),
           std::string("uplink-tx-rx"),
           std::to_string(uplinks.at(i).getTransmit()->getID())+"-"+
            std::to_string(uplinks.at(i).getReceive()->getID())
          );
        }
      }
      for(size_t i=0; i<satellites.size(); i++) {
        const uint32_t SAT_ID = satellites.at(i).getCatalogNumber();
        log.meas(
         comsim::LogLevel::INFO,
         dateTime.toString(),
         std::string("MB-buffered-sat-"+std::to_string(SAT_ID)),
         std::to_string(
          (static_cast<double>(satId2Sensor[SAT_ID]->getBitsBuffered())/8.0)/
          1.0e6
         )
        );
      }
    }
    // Update simulation to the next second
    dateTime.update(10000000); // 1 centisecond
    for(size_t i=0; i<satellites.size(); i++) {
      const uint32_t SAT_ID = satellites.at(i).getCatalogNumber();
      satellites.at(i).update(10000000); // 1 centisecond
      satId2Sensor[SAT_ID]->setECIPosn(satellites.at(i).getECIPosn());
      satId2Sensor[SAT_ID]->update(10000000); // 1 centisecond
    }
    for(size_t i=0; i<groundStations.size(); i++) {
      groundStations.at(i).update(10000000); // 1 centisecond
    }
    centisecondCount+=1;
  }
  // Write out logs
  log.writeAll();
  // Clean up
  for(
   std::map<uint32_t,comsim::Sensor*>::iterator it=satId2Sensor.begin();
   it!=satId2Sensor.end(); it++
  ) {
    delete it->second;
  }
  for(
   std::map<uint32_t,comsim::Transmit*>::iterator it=satId2Tx.begin();
   it!=satId2Tx.end(); it++
  ) {
    delete it->second;
  }
  for(
   std::map<uint32_t,comsim::Transmit*>::iterator it=gndId2Tx.begin();
   it!=gndId2Tx.end(); it++
  ) {
    delete it->second;
  }
  for(
   std::map<uint32_t,comsim::Receive*>::iterator it=satId2Rx.begin();
   it!=satId2Rx.end(); it++
  ) {
    delete it->second;
  }
  for(
   std::map<uint32_t,comsim::Receive*>::iterator it=gndId2Rx.begin();
   it!=gndId2Rx.end(); it++
  ) {
    delete it->second;
  }
  std::exit(EXIT_SUCCESS);
}
