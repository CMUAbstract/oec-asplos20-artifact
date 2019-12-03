# Usage: python3 populate_gnd_unis.py n /path/to/src/ /path/to/dst/
# Input:
#  n: number of university ground stations to be created
#  /path/to/src/: path to directory containing unis.dat
#  /path/to/dst/: path to directory for output files
# Output:
#  CSV file with [id,lat(deg),lon(deg),hae(km)]
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
import random
import sys

CMU_ID = 40079

n   = 1
src = ''
dst = ''

if len(sys.argv)==4:
  n   = int(sys.argv[1])
  src = sys.argv[2]
  if src[-1] != '/':
    src += '/'
  dst = sys.argv[3]
  if dst[-1] != '/':
    dst += '/'
else:
  print("Usage: python3 populate_gnd_unis.py n /path/to/src/ /path/to/dst/")
  exit()

# Parse unis.dat and extract CMU
lines = []
with open(src+'unis.dat','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    ls = line.split(',')
    if int(ls[0])==CMU_ID:
      with open(dst+'ground-station-'+str(int(ls[0])).zfill(10)+'.dat',mode='w',newline='') as outfile:
        csvwriter = csv.writer(outfile)
        csvwriter.writerow(['id','lat','lon','hae'])
        csvwriter.writerow([str(int(ls[0])).zfill(10),'{:+013.9f}'.format(float(ls[2])),'{:+014.9f}'.format(float(ls[3])),'{:+013.9f}'.format(0.0)])
      lines.remove(line)
# Use n and random seed to extract more unis
random.seed(1)
indices = random.sample(range(0,len(lines)),len(lines))
for i in range(0,n-1):
  ls = lines[indices[i]].split(',')
  with open(dst+'ground-station-'+str(int(ls[0])).zfill(10)+'.dat',mode='w',newline='') as outfile:
    csvwriter = csv.writer(outfile)
    csvwriter.writerow(['id','lat','lon','hae'])
    csvwriter.writerow([str(int(ls[0])).zfill(10),'{:+013.9f}'.format(float(ls[2])),'{:+014.9f}'.format(float(ls[3])),'{:+013.9f}'.format(0.0)])
