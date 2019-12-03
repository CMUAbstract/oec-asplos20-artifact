// ChannelType.hpp
// Channel type header file
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

#ifndef COMSIM_CHANNEL_TYPE_HPP
#define COMSIM_CHANNEL_TYPE_HPP

// Standard library
#include <cstdint> // uint8_t

// Channel types
// - DOWNLINK: TX in space, RX on Earth
// - CROSSLINK: TX in space, RX in space
// - UPLINK: TX on Earth, RX in space

namespace comsim {
  enum class ChannelType : uint8_t {
    DOWNLINK    =   1,
    CROSSLINK   =   2,
    UPLINK      =   3,
    UNSPECIFIED = 255
  };
}

#endif
