# Communication Simulation Software

**Current version**: 0.0.0

* This software uses [semantic versioning](http://semver.org).

**Dependencies**

* A C++11 compiler
* CMake for building Makefiles

## Directory Contents

* [channel](channel/README.md): The `Channel` class manages simulation of a
  communication channel.
* [channel-type](channel-type/README.md): The `ChannelType` enum class
  enumerates the channel types: downlink, crosslink, or uplink.
* [constants](constants/README.md): The constants header file collects constants
  from various references.
* [date-time](date-time/README.md): The `DateTime` class implements ISO 8601 and
  represents the Gregorian date and UT1 time in the format
  `YYYY-MM-DDTHH:MM:SS.SSSSSSSSS`.
* [edge](edge/README.md): The `Edge` class represents an edge in a graph.
* [ground-station](ground-station/README.md): The `GroundStation` class manages
  simulation of a ground station and acts as a base class for different kinds of
  ground stations.
* [isim](isim/README.md): The `ISim` abstract class defines an interface for
  simulation.
* [log](log/README.md): The `Log` singleton acts as a central object for all
  event and measurement logs.
* [log-level](log-level/README.md): The `LogLevel` enum class enumerates the log
  levels.
* [receive](receive/README.md): The `Receive` class manages simulation of a
  receiver and acts as a base class for different kinds of receivers.
* [satellite](satellite/README.md): The `Satellite` class manages simulation of
  a satellite and acts as a base class for different kinds of satellites.
* [sensor](sensor/README.md): The `Sensor` class manages simulation of a sensor
  and acts as a base class for different kinds of sensors.
* [transmit](transmit/README.md): The `Transmit` class manages simulation of a
  transmitter and acts as a base class for different kinds of transmitters.
* [utilities](utilities/README.md): The utility functions provide general
  calculations, conversions, and algorithms.
* [vertex](vertex/README.md): The `Vertex` class represents a vertex in a graph.
* [README.md](README.md): This document

## License

Copyright 2019 Bradley Denby

Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at <http://www.apache.org/licenses/LICENSE-2.0>.

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
