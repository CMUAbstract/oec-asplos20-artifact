# Usage: python3 fsfp_latency.py /full/path/to/src/ /full/path/to/dst/
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
import fnmatch
import os
import sys

src = ''
dst = ''

if len(sys.argv)==3:
  src = sys.argv[1]
  if src[-1] != '/':
    src+='/'
  dst = sys.argv[2]
  if dst[-1] != '/':
    dst+='/'
else:
  print('Usage: python3 fsfp_latency.py /full/path/to/src/ /full/path/to/dst/')
  exit()

with open(dst+'fsfp-latency.csv', 'w', newline='') as csvfile:
  csvwriter = csv.writer(csvfile, delimiter=',', quotechar='"')
  csvwriter.writerow(['depth','avg','stdev'])
all_contents = os.listdir(src)
subdirs = []
for e in all_contents:
  if os.path.isdir(src+e):
    subdirs.append(e)
subdirs.sort()
for subdir in subdirs:
  x = int(subdir)
  y_count = 0.0
  y_total = 0.0
  latencies = []
  files = os.listdir(src+subdir)
  begin_pattern = 'event-jetson-*-begin-gtf-*.csv'
  begin_matches = fnmatch.filter(files, begin_pattern)
  begin_matches.sort()
  gtf_to_begin = {}
  for i in range(0,len(begin_matches)):
    begin_dev_ix = 13
    begin_dev_id = ''
    while begin_matches[i][begin_dev_ix].isdigit():
      begin_dev_id += begin_matches[i][begin_dev_ix]
      begin_dev_ix += 1
    begin_gtf_ix = 24+len(begin_dev_id)
    begin_gtf_id = ''
    while begin_matches[i][begin_gtf_ix].isdigit():
      begin_gtf_id += begin_matches[i][begin_gtf_ix]
      begin_gtf_ix += 1
    begin_time = 0.0
    with open(src+subdir+'/'+begin_matches[i],'r',newline='') as readfile:
      csvreader = csv.reader(readfile, delimiter=',', quotechar='"')
      header = next(csvreader)
      begin_time = float(next(csvreader)[0])
    if begin_gtf_id in gtf_to_begin:
      gtf_to_begin[begin_gtf_id] = min(gtf_to_begin[begin_gtf_id],begin_time)
    else:
      gtf_to_begin[begin_gtf_id] = begin_time
  complete_pattern = 'event-jetson-*-complete-gtf-*.csv'
  complete_matches = fnmatch.filter(files, complete_pattern)
  complete_matches.sort()
  gtf_to_complete = {}
  for i in range(0,len(complete_matches)):
    complete_dev_ix = 13
    complete_dev_id = ''
    while complete_matches[i][complete_dev_ix].isdigit():
      complete_dev_id += complete_matches[i][complete_dev_ix]
      complete_dev_ix += 1
    complete_gtf_ix = 27+len(complete_dev_id)
    complete_gtf_id = ''
    while complete_matches[i][complete_gtf_ix].isdigit():
      complete_gtf_id += complete_matches[i][complete_gtf_ix]
      complete_gtf_ix += 1
    complete_time = 0.0
    with open(src+subdir+'/'+complete_matches[i],'r',newline='') as readfile:
      csvreader = csv.reader(readfile, delimiter=',', quotechar='"')
      header = next(csvreader)
      complete_time = float(next(csvreader)[0])
    if complete_gtf_id in gtf_to_complete:
      gtf_to_complete[complete_gtf_id] = max(gtf_to_complete[complete_gtf_id],complete_time)
    else:
      gtf_to_complete[complete_gtf_id] = complete_time
  for begin_key in gtf_to_begin:
    for complete_key in gtf_to_complete:
      if begin_key==complete_key:
        y_count += 1.0
        y_total += (gtf_to_complete[complete_key]-gtf_to_begin[begin_key])
        latencies.append(gtf_to_complete[complete_key]-gtf_to_begin[begin_key])
  avg = y_total/float(y_count)
  stdev = 0.0
  for latency in latencies:
    stdev += pow(latency-avg,2)
  stdev = pow(float(stdev)/float(len(latencies)),0.5)
  with open(dst+'fsfp-latency.csv', 'a', newline='') as csvfile:
    csvwriter = csv.writer(csvfile, delimiter=',', quotechar='"')
    csvwriter.writerow([x,avg,stdev])
