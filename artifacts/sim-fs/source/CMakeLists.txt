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
project(FrameSpaced)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
link_libraries(stdc++fs)
include_directories("../../../software/comsim/channel/include"
                    "../../../software/comsim/channel-type/include"
                    "../../../software/comsim/constants/include"
                    "../../../software/comsim/date-time/include"
                    "../../../software/comsim/edge/include"
                    "../../../software/comsim/ground-station/include"
                    "../../../software/comsim/isim/include"
                    "../../../software/comsim/log/include"
                    "../../../software/comsim/log-level/include"
                    "../../../software/comsim/receive/include"
                    "../../../software/comsim/satellite/include"
                    "../../../software/comsim/sensor/include"
                    "../../../software/comsim/transmit/include"
                    "../../../software/comsim/utilities/include"
                    "../../../software/comsim/vertex/include")
add_executable(frame_spaced frame-spaced.cpp
               ../../../software/comsim/channel/source/Channel.cpp
               ../../../software/comsim/date-time/source/DateTime.cpp
               ../../../software/comsim/edge/source/Edge.cpp
               ../../../software/comsim/ground-station/source/GroundStation.cpp
               ../../../software/comsim/log/source/Log.cpp
               ../../../software/comsim/receive/source/Receive.cpp
               ../../../software/comsim/satellite/source/Satellite.cpp
               ../../../software/comsim/sensor/source/Sensor.cpp
               ../../../software/comsim/transmit/source/Transmit.cpp
               ../../../software/comsim/utilities/source/utilities.cpp
               ../../../software/comsim/vertex/source/Vertex.cpp)
