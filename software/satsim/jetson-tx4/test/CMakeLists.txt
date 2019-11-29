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
project(TestJetsonTX4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("../include"
                    "../../ilog/include"
                    "../../isim/include"
                    "../../iwork/include"
                    "../../logger/include"
                    "../../job/include"
                    "../../energy-consumer/include")
add_executable(test_jetson_tx4 test-jetson-tx4.cpp
               ../source/JetsonTX4.cpp
               ../../logger/source/Logger.cpp
               ../../job/source/Job.cpp
               ../../energy-consumer/source/EnergyConsumer.cpp)
