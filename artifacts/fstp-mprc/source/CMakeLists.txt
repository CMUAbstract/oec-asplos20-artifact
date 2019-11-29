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
project(FSTPMprc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("../../../software/satsim/ilog/include"
                    "../../../software/satsim/isim/include"
                    "../../../software/satsim/iwork/include"
                    "../../../software/satsim/logger/include"
                    "../../../software/satsim/job/include"
                    "../../../software/satsim/energy-harvester/include"
                    "../../../software/satsim/simple-solar-cell/include"
                    "../../../software/satsim/energy-storage/include"
                    "../../../software/satsim/capacitor/include"
                    "../../../software/satsim/energy-consumer/include"
                    "../../../software/satsim/jetson-tx4/include"
                    "../../../software/satsim/mai-adacs/include"
                    "../../../software/satsim/chameleon-imager/include"
                    "../../../software/satsim/eh-system/include"
                    "../../../software/satsim/orbit/include"
                    "../../../software/satsim/satellite/include"
                    "../../../software/satsim/eh-satellite/include")
add_executable(fstp_mprc fstp-mprc.cpp
               ../../../software/satsim/logger/source/Logger.cpp
               ../../../software/satsim/job/source/Job.cpp
               ../../../software/satsim/energy-harvester/source/EnergyHarvester.cpp
               ../../../software/satsim/simple-solar-cell/source/SimpleSolarCell.cpp
               ../../../software/satsim/energy-storage/source/EnergyStorage.cpp
               ../../../software/satsim/capacitor/source/Capacitor.cpp
               ../../../software/satsim/energy-consumer/source/EnergyConsumer.cpp
               ../../../software/satsim/jetson-tx4/source/JetsonTX4.cpp
               ../../../software/satsim/mai-adacs/source/MAIAdacs.cpp
               ../../../software/satsim/chameleon-imager/source/ChameleonImager.cpp
               ../../../software/satsim/eh-system/source/EHSystem.cpp
               ../../../software/satsim/orbit/source/Orbit.cpp
               ../../../software/satsim/satellite/source/Satellite.cpp
               ../../../software/satsim/eh-satellite/source/EHSatellite.cpp)
