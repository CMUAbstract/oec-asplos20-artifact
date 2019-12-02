#!/bin/bash
#
# generate_plots.sh
# A bash script that generates the plots
#
# Usage: ./generate_f7_plots.sh
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

./generate_f6_plots.sh
./generate_f7_plots.sh
./generate_f8_plots.sh
echo "Plots should be available in '../plots/'."
