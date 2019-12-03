#!/bin/bash
#
# process_f6_logs.sh
# A bash script that collates the downlink deficits
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
