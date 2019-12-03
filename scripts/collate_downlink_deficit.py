# Usage: python3 collate_downlink_deficit.py /path/to/logs/ /path/to/file.csv mb_per_collect x_value
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

import csv
import os
import sys

log_dir = ''
out_fil = ''
sensemb = 0.0
x_value = 0

if len(sys.argv)==5 and sys.argv[2][-4:]=='.csv':
  log_dir = sys.argv[1]
  if log_dir[-1] != '/':
    log_dir += '/'
  out_fil = sys.argv[2]
  sensemb = float(sys.argv[3])
  x_value = int(sys.argv[4])
else:
  print("Usage: python3 collate_downlink_deficit.py /path/to/logs/ /path/to/file.csv mb_per_collect x_value")
  exit()

sensetl = 0.0
with open(log_dir+'evnt-trigger-time.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  sensetl = float(len(lines))*sensemb

sensedl = 0.0
with open(log_dir+'meas-downlink-MB.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    sensedl += float(line.split(',')[1])

with open(out_fil,mode='a',newline='') as outfile:
  csvwriter = csv.writer(outfile)
  csvwriter.writerow([str(x_value).zfill(3),'{:010.6f}'.format(100.0*max(0.0,1.0-sensedl/sensetl))])

