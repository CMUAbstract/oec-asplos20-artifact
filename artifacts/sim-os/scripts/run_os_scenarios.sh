#!/bin/bash
# Usage: ./run_os_scenarios.sh path/to/name
#
# run_os_scenarios.sh
# A bash script that runs all scenarios
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

baseline=$( ps -u $(whoami) | sed 1d | wc -l )
./prep_os_scenarios.sh
cd ../build/
CC=$HOME/sw/gcc-8.3.0-install/bin/gcc CXX=$HOMEsw/gcc-8.3.0-install/bin/g++ \
 LD_LIBRARY_PATH=$HOME/sw/gcc-8.3.0-install/lib64/ cmake ../source/
make
for orbit in planet spacex spire
do
  for gnd_count in 010 020 030 040 050 060 070 080 090 100 110 120
  do
    # equatorial ground stations
    gnd_config=eq
    ./orbit_spaced ../logs/$orbit-$gnd_config-$gnd_count/ \
                   ../data/$orbit-$gnd_config-$gnd_count/dt/ \
                   ../data/$orbit-$gnd_config-$gnd_count/sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/sensor/ \
                   ../data/$orbit-$gnd_config-$gnd_count/gnd/ \
                   ../data/$orbit-$gnd_config-$gnd_count/tx-sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/tx-gnd/ \
                   ../data/$orbit-$gnd_config-$gnd_count/rx-sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/rx-gnd/ &
    # north/south polar ground stations
    gnd_config=ns
    ./orbit_spaced ../logs/$orbit-$gnd_config-$gnd_count/ \
                   ../data/$orbit-$gnd_config-$gnd_count/dt/ \
                   ../data/$orbit-$gnd_config-$gnd_count/sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/sensor/ \
                   ../data/$orbit-$gnd_config-$gnd_count/gnd/ \
                   ../data/$orbit-$gnd_config-$gnd_count/tx-sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/tx-gnd/ \
                   ../data/$orbit-$gnd_config-$gnd_count/rx-sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/rx-gnd/ &
    # university ground stations
    gnd_config=un
    ./orbit_spaced ../logs/$orbit-$gnd_config-$gnd_count/ \
                   ../data/$orbit-$gnd_config-$gnd_count/dt/ \
                   ../data/$orbit-$gnd_config-$gnd_count/sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/sensor/ \
                   ../data/$orbit-$gnd_config-$gnd_count/gnd/ \
                   ../data/$orbit-$gnd_config-$gnd_count/tx-sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/tx-gnd/ \
                   ../data/$orbit-$gnd_config-$gnd_count/rx-sat/ \
                   ../data/$orbit-$gnd_config-$gnd_count/rx-gnd/ &
    # if necessary, wait for cores to free
    while (( $(( $( ps -u $(whoami) | sed 1d | wc -l ) - $baseline )) > $(nproc) ))
    do
      sleep 1000
    done
  done
done
