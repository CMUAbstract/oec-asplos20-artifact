#!/bin/bash
#
# generate_f8_plots.sh
# A bash script that generates the latency plots
#
# Usage: ./generate_f8_plots.sh
# Arguments: None; assumes execution from the top-level scripts directory.
# Outputs: Latency plot files
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

source p3-env/bin/activate
python3 plot_f8a.py ../artifacts/ ../plots/
python3 plot_f8b.py ../artifacts/ ../plots/
python3 plot_f8c.py ../artifacts/ ../plots/
python3 plot_f8d.py ../artifacts/ ../plots/
deactivate
