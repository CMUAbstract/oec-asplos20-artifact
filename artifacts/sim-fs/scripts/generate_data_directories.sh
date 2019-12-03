#!/bin/bash
# Usage: ./generate_data_directories.sh path/to/name
#
# generate_data_directories.sh
# A bash script that generates the standard set of data directories at the
# specified path
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
