#!/bin/bash
#
# generate_f6_plots.sh
# A bash script that generates the downlink deficit plots
#
# Usage: ./generate_f6_plots.sh
# Arguments: None; assumes execution from the top-level scripts directory.
# Outputs: Downlink deficit plot files
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
python3 plot_f6a.py ../artifacts/ ../plots/
python3 plot_f6b.py ../artifacts/ ../plots/
python3 plot_f6c.py ../artifacts/ ../plots/
deactivate
