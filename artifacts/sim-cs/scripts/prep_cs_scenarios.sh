#!/bin/bash
# Usage: ./prep_cs_scenarios.sh
#  Run ./prep_cs_scenarios.sh from the same directory as the following files:
#   - generate_data_directories.sh, populate_gnd_ring.py, populate_gnd_unis.py,
#     populate_rx.py, populate_tx.py
#  The following data directories must also be present (sim-common):
#   - cs-planet-tles, cs-spacex-tles, cs-spire-tles, dt, sensor, unis
#  The scenario input data files for 108 close-spaced scenarios are generated.
#   - 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120 ground stations (12)
#   - equatorial, north/south polar, and university ground station placement (3)
#   - Planet, SpaceX, and Spire orbits parameters (3)
#   - 12*3*3 = 108
#
# prep_cs_scenarios.sh
# A bash script that prepares all scenarios
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

# Generate data directory if necessary
if [ ! -d ../data ]
then
  mkdir ../data
fi
# Generate logs directory if necessary
if [ ! -d ../logs ]
then
  mkdir ../logs
fi
# Generate data and logs sub-directories
for orbit in planet spacex spire
do
  for gnd_count in 010 020 030 040 050 060 070 080 090 100 110 120
  do
    # equatorial ground stations
    gnd_config=eq
    ./generate_data_directories.sh ../data/$orbit-$gnd_config-$gnd_count/
    cp ../../sim-common/dt/date-time.dat ../data/$orbit-$gnd_config-$gnd_count/dt/
    cp ../../sim-common/sat/$orbit.tle ../data/$orbit-$gnd_config-$gnd_count/sat/
    cp ../../sim-common/sat/cs-$orbit.dat ../data/$orbit-$gnd_config-$gnd_count/sat/
    cp ../../sim-common/sensor/sensor.dat ../data/$orbit-$gnd_config-$gnd_count/sensor/
    python3 populate_gnd_ring.py 0.0 0.0 $((10#$gnd_count)) 0 ../data/$orbit-$gnd_config-$gnd_count/gnd/
    python3 populate_rx.py ../data/$orbit-$gnd_config-$gnd_count/gnd/ dat 44.1 8.15e9 20.0e6 ../data/$orbit-$gnd_config-$gnd_count/rx-gnd/
    python3 populate_rx.py ../data/$orbit-$gnd_config-$gnd_count/sat/ tle 1.5 436.5e6 60.0e3 ../data/$orbit-$gnd_config-$gnd_count/rx-sat/
    python3 populate_tx.py ../data/$orbit-$gnd_config-$gnd_count/gnd/ dat 10.0 -1.0 15.5 436.5e6 60.0e3 ../data/$orbit-$gnd_config-$gnd_count/tx-gnd/
    python3 populate_tx.py ../data/$orbit-$gnd_config-$gnd_count/sat/ tle 2.0 -1.0 6.0 8.15e9 20.0e6 ../data/$orbit-$gnd_config-$gnd_count/tx-sat/
    if [ ! -d ../logs/$orbit-$gnd_config-$gnd_count ]
    then
      mkdir ../logs/$orbit-$gnd_config-$gnd_count
    fi
    # north/south polar ground stations
    gnd_config=ns
    ./generate_data_directories.sh ../data/$orbit-$gnd_config-$gnd_count/
    cp ../../sim-common/dt/date-time.dat ../data/$orbit-$gnd_config-$gnd_count/dt/
    cp ../../sim-common/sat/$orbit.tle ../data/$orbit-$gnd_config-$gnd_count/sat/
    cp ../../sim-common/sat/cs-$orbit.dat ../data/$orbit-$gnd_config-$gnd_count/sat/
    cp ../../sim-common/sensor/sensor.dat ../data/$orbit-$gnd_config-$gnd_count/sensor/
    python3 populate_gnd_ring.py  87.0 0.0 $(( $((10#$gnd_count))/2 )) 90000 ../data/$orbit-$gnd_config-$gnd_count/gnd/
    python3 populate_gnd_ring.py -87.0 0.0 $(( $((10#$gnd_count))/2 )) 91000 ../data/$orbit-$gnd_config-$gnd_count/gnd/
    python3 populate_rx.py ../data/$orbit-$gnd_config-$gnd_count/gnd/ dat 44.1 8.15e9 20.0e6 ../data/$orbit-$gnd_config-$gnd_count/rx-gnd/
    python3 populate_rx.py ../data/$orbit-$gnd_config-$gnd_count/sat/ tle 1.5 436.5e6 60.0e3 ../data/$orbit-$gnd_config-$gnd_count/rx-sat/
    python3 populate_tx.py ../data/$orbit-$gnd_config-$gnd_count/gnd/ dat 10.0 -1.0 15.5 436.5e6 60.0e3 ../data/$orbit-$gnd_config-$gnd_count/tx-gnd/
    python3 populate_tx.py ../data/$orbit-$gnd_config-$gnd_count/sat/ tle 2.0 -1.0 6.0 8.15e9 20.0e6 ../data/$orbit-$gnd_config-$gnd_count/tx-sat/
    if [ ! -d ../logs/$orbit-$gnd_config-$gnd_count ]
    then
      mkdir ../logs/$orbit-$gnd_config-$gnd_count
    fi
    # university ground stations
    gnd_config=un
    ./generate_data_directories.sh ../data/$orbit-$gnd_config-$gnd_count/
    cp ../../sim-common/dt/date-time.dat ../data/$orbit-$gnd_config-$gnd_count/dt/
    cp ../../sim-common/sat/$orbit.tle ../data/$orbit-$gnd_config-$gnd_count/sat/
    cp ../../sim-common/sat/cs-$orbit.dat ../data/$orbit-$gnd_config-$gnd_count/sat/
    cp ../../sim-common/sensor/sensor.dat ../data/$orbit-$gnd_config-$gnd_count/sensor/
    python3 populate_gnd_unis.py $((10#$gnd_count)) ../../sim-common/unis/ ../data/$orbit-$gnd_config-$gnd_count/gnd/
    python3 populate_rx.py ../data/$orbit-$gnd_config-$gnd_count/gnd/ dat 44.1 8.15e9 20.0e6 ../data/$orbit-$gnd_config-$gnd_count/rx-gnd/
    python3 populate_rx.py ../data/$orbit-$gnd_config-$gnd_count/sat/ tle 1.5 436.5e6 60.0e3 ../data/$orbit-$gnd_config-$gnd_count/rx-sat/
    python3 populate_tx.py ../data/$orbit-$gnd_config-$gnd_count/gnd/ dat 10.0 -1.0 15.5 436.5e6 60.0e3 ../data/$orbit-$gnd_config-$gnd_count/tx-gnd/
    python3 populate_tx.py ../data/$orbit-$gnd_config-$gnd_count/sat/ tle 2.0 -1.0 6.0 8.15e9 20.0e6 ../data/$orbit-$gnd_config-$gnd_count/tx-sat/
    if [ ! -d ../logs/$orbit-$gnd_config-$gnd_count ]
    then
      mkdir ../logs/$orbit-$gnd_config-$gnd_count
    fi
  done
done
