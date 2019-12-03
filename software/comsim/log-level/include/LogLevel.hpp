// LogLevel.hpp
// Log level header file
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

#ifndef COMSIM_LOG_LEVEL_HPP
#define COMSIM_LOG_LEVEL_HPP

// Standard library
#include <cstdint> // uint8_t

// Log level guidance, modified from https://stackoverflow.com/a/2031209
// - NONE  (00000001): Suppress all logs
// - FATAL (00000010): The application must be shutdown.
// - ERROR (00000100): The algorithm cannot proceed, but the application could.
// - WARN  (00001000): The application is automatically recovering from misuse.
// - INFO  (00010000): Configuration parameters, service start/stop
// - DEBUG (00100000): Diagnostics useful to IT, sysadmins, etc.
// - TRACE (01000000): Used when tracing through to code during development
// - ALL   (01111110): TRACE|DEBUG|INFO|WARN|ERROR|FATAL

namespace comsim {
  enum class LogLevel : uint8_t {
    NONE  =   1,
    FATAL =   2,
    ERROR =   4,
    WARN  =   8,
    INFO  =  16,
    DEBUG =  32,
    TRACE =  64,
    ALL   = 126
  };
}

#endif
