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

Written by Bradley Denby  
Other contributors: None

To the extent possible under law, the author(s) have dedicated all copyright and
related and neighboring rights to this work to the public domain worldwide. This
work is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication with this
work. If not, see <https://creativecommons.org/publicdomain/zero/1.0/>.
