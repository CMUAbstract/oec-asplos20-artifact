// ISim.hpp
// ISim interace file
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

#ifndef COMSIM_ISIM_HPP
#define COMSIM_ISIM_HPP

// Standard library
#include <cstdint> // uint32_t, uint8_t

// comsim
// None

namespace comsim {
  class ISim {
  public:
    virtual void update(const uint32_t& nanosecond) = 0;
    virtual void update(const uint8_t& second, const uint32_t& nanosecond) = 0;
    virtual void update(
     const uint8_t& minute, const uint8_t& second, const uint32_t& nanosecond
    ) = 0;
    virtual void update(
     const uint8_t& hour, const uint8_t& minute, const uint8_t& second,
     const uint32_t& nanosecond
    ) = 0;
  };
}

#endif
