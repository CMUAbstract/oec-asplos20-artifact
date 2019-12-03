# Usage: python3 fsfp_coverage.py /full/path/to/src/ /full/path/to/dst/
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
import math
import os
import sys

src = ''
dst = ''
gtf_count = 1642

if len(sys.argv)==3:
  src = sys.argv[1]
  if src[-1] != '/':
    src+='/'
  dst = sys.argv[2]
  if dst[-1] != '/':
    dst+='/'
else:
  print("Usage: python3 fsfp_coverage.py /full/path/to/src/ /full/path/to/dst/")
  exit()

with open(dst+'fsfp-coverage.csv', 'w', newline='') as csvfile:
  csvwriter = csv.writer(csvfile, delimiter=',', quotechar='"')
  csvwriter.writerow(['depth','capture-coverage'])
all_contents = os.listdir(src)
subdirs = []
for e in all_contents:
  if os.path.isdir(src+e):
    subdirs.append(e)
subdirs.sort()
for subdir in subdirs:
  x = int(subdir)
  y_count = 0.0
  files = os.listdir(src+subdir)
  capture_pattern = 'event-chamgr-*-readout-gtf-*.csv'
  capture_matches = fnmatch.filter(files, capture_pattern)
  for i in range(0,len(capture_matches)):
    y_count += 1.0
  y = float(y_count)/float(gtf_count)
  with open(dst+'fsfp-coverage.csv', 'a', newline='') as csvfile:
    csvwriter = csv.writer(csvfile, delimiter=',', quotechar='"')
    csvwriter.writerow([x,y])
