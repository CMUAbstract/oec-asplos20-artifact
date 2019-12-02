# Usage: python3 plot_f7b.py /path/to/src/ /path/to/dst/
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
  print("Usage: python3 plot_f7b.py /path/to/src/ /path/to/dst/")
  exit()

# Baseline
base_xvalues = []
base_yvalues = []
with open(src+'fsfp-base/logs/fsfp-latency.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    base_xvalues.append(int(line_split[0]))
    base_yvalues.append(float(line_split[1]))
# More capacitance
mcap_xvalues = []
mcap_yvalues = []
with open(src+'fsfp-mcap/logs/fsfp-latency.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    mcap_xvalues.append(int(line_split[0]))
    mcap_yvalues.append(float(line_split[1]))
# More power
mpow_xvalues = []
mpow_yvalues = []
with open(src+'fsfp-mpow/logs/fsfp-latency.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    mpow_xvalues.append(int(line_split[0]))
    mpow_yvalues.append(float(line_split[1]))
# More compute
mprc_xvalues = []
mprc_yvalues = []
with open(src+'fsfp-mprc/logs/fsfp-latency.csv','r') as infile:
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
ymin = 0
ymax = 400
ystep = 50
fig = plt.figure()
ax  = plt.axes(\
 title='Frame-spaced, frame-parallel', \
 xlabel='Device count', \
 xlim=(xmin,xmax), xscale='linear', \
 xticks=[x for x in range(xmin,xmax+xstep,xstep)], \
 xticklabels=[str(x) for x in range(xmin,xmax+xstep,xstep)], \
 ylabel='Seconds', \
 ylim=(ymin,ymax), yscale='linear', \
 yticks=[y for y in range(ymin,ymax+ystep,ystep)], \
 yticklabels=[str(y) for y in range(ymin,ymax+ystep,ystep)] \
)
ax.plot(base_xvalues,base_yvalues,color='#000000',linestyle='solid',marker='2')
ax.plot(mcap_xvalues,mcap_yvalues,color='#bb0000',linestyle='solid',marker='4')
ax.plot(mpow_xvalues,mpow_yvalues,color='#224477',linestyle='solid',marker='1')
ax.plot(mprc_xvalues,mprc_yvalues,color='#008855',linestyle='solid',marker='3')
fig.savefig(dst+'fsfp.pdf',bbox_inches='tight')
plt.close(fig)
