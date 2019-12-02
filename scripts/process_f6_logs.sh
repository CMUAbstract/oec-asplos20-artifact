#!/bin/bash
#
# collate_downlink_deficits.sh
# A bash script that collates the downlink deficits
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

function get_mb_per_collect {
  if [ "$1" == "cs" ]
  then
    if [ "$2" == "planet" ]
    then
      echo "3.039880125"
    elif [ "$2" == "spacex" ]
    then
      echo "3.039880125"
    elif [ "$2" == "spire" ]
    then
      echo "3.039880125"
    else
      echo "0.0"
    fi
  elif [ "$1" == "fs" ]
  then
    if [ "$2" == "planet" ]
    then
      echo "653.574226875"
    elif [ "$2" == "spacex" ]
    then
      echo "182.3928075"
    elif [ "$2" == "spire" ]
    then
      echo "252.310050375"
    else
      echo "0.0"
    fi
  elif [ "$1" == "os" ]
  then
    if [ "$2" == "planet" ]
    then
      echo "653.574226875"
    elif [ "$2" == "spacex" ]
    then
      echo "182.3928075"
    elif [ "$2" == "spire" ]
    then
      echo "252.310050375"
    else
      echo "0.0"
    fi
  else
    echo "0.0"
  fi
}

for sat_config in cs fs os
do
  for constellation in planet spacex spire
  do
    mb_per_collect="$( get_mb_per_collect $sat_config $constellation )"
    for gnd_config in eq ns un
    do
      log_prefix=../artifacts/sim-$sat_config/logs/$constellation-$gnd_config
      out_file=../artifacts/sim-$sat_config/logs/$sat_config-$constellation-$gnd_config.csv
      touch $out_file
      echo "gnd-count,percent" > $out_file
      echo "000,100.000000" >> $out_file
      for gnd_count in 010 020 030 040 050 060 070 080 090 100 110 120
      do
        python3 collate_downlink_deficit.py $log_prefix-$gnd_count/ $out_file $mb_per_collect $gnd_count
      done
    done
  done
done
