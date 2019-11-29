# Satellite Simulation Software

**Current version**: 0.0.0

* This software uses [semantic versioning](http://semver.org).

**Dependencies**

* A C++11 compiler
* CMake for building Makefiles

## Directory Contents

* [capacitor](capacitor/README.md): A dervied class of the `EnergyStorage` class
* [chameleon-imager](chameleon-imager/README.md): A dervied class of the
  `EnergyConsumer` class
* [eh-satellite](eh-satellite/README.md): A dervied class of the `Satellite`
  class
* [eh-system](eh-system/README.md): A class to manage simulation of a system
  composed of an energy harvester, an energy buffer, and energy consumers
* [energy-consumer](energy-consumer/README.md): A base class for
  energy-consuming devices
* [energy-harvester](energy-harvester/README.md): A base class for
  energy-harvesting devices
* [energy-storage](energy-storage/README.md): A base class for energy-storing
  devices
* [ilog](ilog/README.md): An abstract class that defines an interface for
  logging events and measurements
* [isim](isim/README.md): An abstract class that defines an interface for
  simulation
* [iwork](iwork/README.md): An abstract class that defines an interface for
  working on jobs
* [jetson-tx2](jetson-tx2/README.md): A dervied class of the `EnergyConsumer`
  class
* [job](job/README.md): A class that manages workers completing tasks
* [logger](logger/README.md): A singleton acting as a central repository for all
  event and measurement logs
* [mai-adacs](mai-adacs/README.md): A dervied class of the `EnergyConsumer`
  class
* [orbit](orbit/README.md): A class that manages simulation of an orbit
* [satellite](satellite/README.md): A class acting as a base class for different
  kinds of satellites
* [simple-solar-cell](simple-solar-cell/README.md): A dervied class of the
  `EnergyHarvester` class
* [xlink](xlink/README.md): A dervied class of the `EnergyConsumer` class
* [README.md](README.md): This document

## License

Written by Bradley Denby  
Other contributors: None

To the extent possible under law, the author(s) have dedicated all copyright and
related and neighboring rights to this work to the public domain worldwide. This
work is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication with this
work. If not, see <https://creativecommons.org/publicdomain/zero/1.0/>.
