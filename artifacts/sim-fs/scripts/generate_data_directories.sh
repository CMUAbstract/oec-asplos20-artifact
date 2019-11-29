#!/bin/bash
# Usage: ./generate_data_directories.sh path/to/name
#
# generate_data_directories.sh
# A bash script that generates the standard set of data directories at the
# specified path
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

path=$1
if [ ! -d "$path" ]
then
  mkdir "$path"
  if [ ! -d "$path/dt" ]
  then
    mkdir "$path/dt"
  fi
  if [ ! -d "$path/gnd" ]
  then
    mkdir "$path/gnd"
  fi
  if [ ! -d "$path/rx-gnd" ]
  then
    mkdir "$path/rx-gnd"
  fi
  if [ ! -d "$path/rx-sat" ]
  then
    mkdir "$path/rx-sat"
  fi
  if [ ! -d "$path/sat" ]
  then
    mkdir "$path/sat"
  fi
  if [ ! -d "$path/sensor" ]
  then
    mkdir "$path/sensor"
  fi
  if [ ! -d "$path/tx-gnd" ]
  then
    mkdir "$path/tx-gnd"
  fi
  if [ ! -d "$path/tx-sat" ]
  then
    mkdir "$path/tx-sat"
  fi
fi
