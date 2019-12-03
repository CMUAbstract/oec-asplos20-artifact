# Usage: python3 plot_f8d.py /path/to/src/ /path/to/dst/
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
import math
import matplotlib.pyplot as plt
import numpy as np
import os
import sys

src = ''
dst = ''

if len(sys.argv)==3:
  src = sys.argv[1]
  if src[-1] != '/':
    src += '/'
  dst = sys.argv[2]
  if dst[-1] != '/':
    dst += '/'
else:
  print("Usage: python3 plot_f8d.py /path/to/src/ /path/to/dst/")
  exit()

# Baseline
base_xvalues = []
base_yvalues = []
with open(src+'fsfp-base/logs/fsfp-coverage.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    base_xvalues.append(int(line_split[0]))
    base_yvalues.append(float(line_split[1]))
# More capacitance
mcap_xvalues = []
mcap_yvalues = []
with open(src+'fsfp-mcap/logs/fsfp-coverage.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    mcap_xvalues.append(int(line_split[0]))
    mcap_yvalues.append(float(line_split[1]))
# More power
mpow_xvalues = []
mpow_yvalues = []
with open(src+'fsfp-mpow/logs/fsfp-coverage.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    mpow_xvalues.append(int(line_split[0]))
    mpow_yvalues.append(float(line_split[1]))
# More compute
mprc_xvalues = []
mprc_yvalues = []
with open(src+'fsfp-mprc/logs/fsfp-coverage.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    mprc_xvalues.append(int(line_split[0]))
    mprc_yvalues.append(float(line_split[1]))
# Generate plot
xmin = 0
xmax = 400
xstep = 50
ymin = 0.0
ymax = 1.01
ystep = 0.25
fig = plt.figure()
ax  = plt.axes(\
 title='Frame-spaced, frame-parallel', \
 xlabel='Device count', \
 xlim=(xmin,xmax), xscale='linear', \
 xticks=[x for x in range(xmin,xmax+xstep,xstep)], \
 xticklabels=[str(x) for x in range(xmin,xmax+xstep,xstep)], \
 ylabel='Fraction', \
 ylim=(ymin,ymax), yscale='linear', \
 yticks=[y for y in np.arange(ymin,ymax,ystep)], \
 yticklabels=['{:.2f}'.format(y) for y in np.arange(ymin,ymax,ystep)] \
)
ax.plot(base_xvalues,base_yvalues,color='#000000',linestyle='solid',marker='2',label='Baseline')
ax.plot(mcap_xvalues,mcap_yvalues,color='#bb0000',linestyle='solid',marker='4',label='More Capacitance')
ax.plot(mpow_xvalues,mpow_yvalues,color='#224477',linestyle='solid',marker='1',label='More Power')
ax.plot(mprc_xvalues,mprc_yvalues,color='#008855',linestyle='solid',marker='3',label='More Compute')
ax.legend()
fig.savefig(dst+'fsfp-coverage.pdf',bbox_inches='tight')
plt.close(fig)
