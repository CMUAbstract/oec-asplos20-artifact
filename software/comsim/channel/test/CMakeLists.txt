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
project(TestChannel)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("../include"
                    "../../channel-type/include"
                    "../../constants/include"
                    "../../date-time/include"
                    "../../edge/include"
                    "../../isim/include"
                    "../../log/include"
                    "../../log-level/include"
                    "../../receive/include"
                    "../../transmit/include"
                    "../../utilities/include"
                    "../../vertex/include")
add_executable(test_channel test-channel.cpp
               ../source/Channel.cpp
               ../../date-time/source/DateTime.cpp
               ../../edge/source/Edge.cpp
               ../../log/source/Log.cpp
               ../../receive/source/Receive.cpp
               ../../transmit/source/Transmit.cpp
               ../../utilities/source/utilities.cpp
               ../../vertex/source/Vertex.cpp)
