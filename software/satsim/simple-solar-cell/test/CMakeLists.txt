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
project(TestSimpleSolarCell)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("../include"
                    "../../ilog/include"
                    "../../isim/include"
                    "../../logger/include"
                    "../../energy-harvester/include")
add_executable(test_simple_solar_cell test-simple-solar-cell.cpp
               ../source/SimpleSolarCell.cpp
               ../../logger/source/Logger.cpp
               ../../energy-harvester/source/EnergyHarvester.cpp)
