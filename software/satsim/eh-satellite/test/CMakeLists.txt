# CMakeLists.txt
# CMakeLists.txt file
#
# Written by Bradley Denby
# Other contributors: None
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication with this
# software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

cmake_minimum_required(VERSION 3.0)
project(TestEHSatellite)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("../include"
                    "../../ilog/include"
                    "../../isim/include"
                    "../../logger/include"
                    "../../energy-harvester/include"
                    "../../simple-solar-cell/include"
                    "../../energy-storage/include"
                    "../../capacitor/include"
                    "../../energy-consumer/include"
                    "../../jetson-tx2/include"
                    "../../eh-system/include"
                    "../../orbit/include"
                    "../../satellite/include")
add_executable(test_eh_satellite test-eh-satellite.cpp
               ../source/EHSatellite.cpp
               ../../logger/source/Logger.cpp
               ../../energy-harvester/source/EnergyHarvester.cpp
               ../../simple-solar-cell/source/SimpleSolarCell.cpp
               ../../energy-storage/source/EnergyStorage.cpp
               ../../capacitor/source/Capacitor.cpp
               ../../energy-consumer/source/EnergyConsumer.cpp
               ../../jetson-tx2/source/JetsonTX2.cpp
               ../../eh-system/source/EHSystem.cpp
               ../../orbit/source/Orbit.cpp
               ../../satellite/source/Satellite.cpp)
