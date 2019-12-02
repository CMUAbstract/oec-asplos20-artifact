# Usage: python3 cstp_coverage.py /full/path/to/src/ /full/path/to/dst/
#
# Written by Bradley Denby  
# Other contributors: None
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this work to the public domain
# worldwide. This work is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication with this
# work. If not, see <https://creativecommons.org/publicdomain/zero/1.0/>.

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
  print("Usage: python3 cstp_coverage.py /full/path/to/src/ /full/path/to/dst/")
  exit()

with open(dst+'cstp-coverage.csv', 'w', newline='') as csvfile:
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
    y_count += 1.0/float(x)
  y = float(y_count)/float(gtf_count)
  with open(dst+'cstp-coverage.csv', 'a', newline='') as csvfile:
    csvwriter = csv.writer(csvfile, delimiter=',', quotechar='"')
    csvwriter.writerow([x,y])
