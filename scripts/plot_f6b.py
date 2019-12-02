# Usage: python3 plot_f6b.py /path/to/src/ /path/to/dst/
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
  print("Usage: python3 plot_f6b.py /path/to/src/ /path/to/dst/")
  exit()

# Equatorial
eq_xvalues = []
eq_yvalues = []
with open(src+'sim-fs/logs/fs-spire-eq.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    eq_xvalues.append(int(line_split[0]))
    eq_yvalues.append(float(line_split[1]))
# Polar
ns_xvalues = []
ns_yvalues = []
with open(src+'sim-fs/logs/fs-spire-ns.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    ns_xvalues.append(int(line_split[0]))
    ns_yvalues.append(float(line_split[1]))
# University
un_xvalues = []
un_yvalues = []
with open(src+'sim-fs/logs/fs-spire-un.csv','r') as infile:
  lines = infile.readlines()
  lines = lines[1:]
  for line in lines:
    line_split = line.split(',')
    un_xvalues.append(int(line_split[0]))
    un_yvalues.append(float(line_split[1]))
# Generate plot
xmin = 0
xmax = 120
xstep = 10
ymin = 0.0
ymax = 101.0
ystep = 20.0
fig = plt.figure()
ax  = plt.axes(\
 title='Frame-spaced, 3.01 inclination, 83 nanosatellites', \
 xlabel='Number of Ground Stations', \
 xlim=(xmin,xmax), xscale='linear', \
 xticks=[x for x in range(xmin,xmax+xstep,xstep)], \
 xticklabels=[str(x) for x in range(xmin,xmax+xstep,xstep)], \
 ylabel='Percent Data not Downlinked', \
 ylim=(ymin,ymax), yscale='linear', \
 yticks=[y for y in np.arange(ymin,ymax,ystep)], \
 yticklabels=['{:.0f}'.format(y) for y in np.arange(ymin,ymax,ystep)] \
)
ax.plot(eq_xvalues,eq_yvalues,color='#008855',linestyle='solid',marker='2',label='Equatorial')
ax.plot(ns_xvalues,ns_yvalues,color='#224477',linestyle='solid',marker='4',label='Polar')
ax.plot(un_xvalues,un_yvalues,color='#aa6600',linestyle='solid',marker='1',label='University')
ax.legend()
fig.savefig(dst+'downlink-deficit-fs.pdf',bbox_inches='tight')
plt.close(fig)
