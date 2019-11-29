#!/bin/bash
# Usage: ./run_os_scenarios.sh path/to/name
#
# run_os_scenarios.sh
# A bash script that runs all scenarios
#
# Written by Bradley Denby
# Other contributors: None
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication with this
# software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

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
