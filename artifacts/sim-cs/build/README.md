# Compilation and Testing

Compilation is managed by CMake to facilitate straightforward compilation on
multiple platforms. Ensure that CMake is installed before proceeding. A
CMakeLists.txt file should be available in the test directory.

This simulation requires support for C++17, which is provided by GCC 8.

## Compile

Execute the following commands.

```bash
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/sim-cs/build/
CC=$HOME/sw/gcc-8.3.0-install/bin/gcc CXX=$HOME/sw/gcc-8.3.0-install/bin/g++ \
 LD_LIBRARY_PATH=$HOME/sw/gcc-8.3.0-install/lib64/ cmake ../source/
make
```

## Run

After compilation, run the executable.

```bash
./close_spaced ../logs/exp ../data/exp/dt ../data/exp/sat ../data/exp/gnd \
 ../data/exp/tx-sat ../data/exp/tx-gnd ../data/exp/rx-sat ../data/exp/rx-gnd
```

## License

Copyright 2019 Bradley Denby

Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at <http://www.apache.org/licenses/LICENSE-2.0>.

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
