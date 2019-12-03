# CMakeLists.txt
# CMakeLists.txt file
#
# Copyright 2019 Bradley Denby
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at <http://www.apache.org/licenses/LICENSE-2.0>.
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

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
