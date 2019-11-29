// ChannelType.hpp
// Channel type header file
//
// Written by Bradley Denby
// Other contributors: None
//
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication with this
// software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

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
