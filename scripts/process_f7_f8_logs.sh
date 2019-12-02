#!/bin/bash
#
# process_f7_f8_logs.sh
# A bash script that processes the logs used to generate Figure 7 and Figure 8.
# Specifically, this script collates logs from csfp-*, cstp-*, fsfp-*, fstp-*.
#
# Usage: ./process_f7_f8_logs.sh
# Arguments: None; assumes execution from the top-level scripts directory.
# Outputs: Collated log files
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

# Close-spaced, frame-parallel
python3 csfp_coverage.py ../artifacts/csfp-base/logs/ ../artifacts/csfp-base/logs/
python3 csfp_latency.py ../artifacts/csfp-base/logs/ ../artifacts/csfp-base/logs/
python3 csfp_coverage.py ../artifacts/csfp-mcap/logs/ ../artifacts/csfp-mcap/logs/
python3 csfp_latency.py ../artifacts/csfp-mcap/logs/ ../artifacts/csfp-mcap/logs/
python3 csfp_coverage.py ../artifacts/csfp-mpow/logs/ ../artifacts/csfp-mpow/logs/
python3 csfp_latency.py ../artifacts/csfp-mpow/logs/ ../artifacts/csfp-mpow/logs/
python3 csfp_coverage.py ../artifacts/csfp-mprc/logs/ ../artifacts/csfp-mprc/logs/
python3 csfp_latency.py ../artifacts/csfp-mprc/logs/ ../artifacts/csfp-mprc/logs/
# Close-spaced, tile-parallel
python3 cstp_coverage.py ../artifacts/cstp-base/logs/ ../artifacts/cstp-base/logs/
python3 cstp_latency.py ../artifacts/cstp-base/logs/ ../artifacts/cstp-base/logs/
python3 cstp_coverage.py ../artifacts/cstp-mcap/logs/ ../artifacts/cstp-mcap/logs/
python3 cstp_latency.py ../artifacts/cstp-mcap/logs/ ../artifacts/cstp-mcap/logs/
python3 cstp_coverage.py ../artifacts/cstp-mpow/logs/ ../artifacts/cstp-mpow/logs/
python3 cstp_latency.py ../artifacts/cstp-mpow/logs/ ../artifacts/cstp-mpow/logs/
python3 cstp_coverage.py ../artifacts/cstp-mprc/logs/ ../artifacts/cstp-mprc/logs/
python3 cstp_latency.py ../artifacts/cstp-mprc/logs/ ../artifacts/cstp-mprc/logs/
# Frame-spaced, frame-parallel
python3 fsfp_coverage.py ../artifacts/fsfp-base/logs/ ../artifacts/fsfp-base/logs/
python3 fsfp_latency.py ../artifacts/fsfp-base/logs/ ../artifacts/fsfp-base/logs/
python3 fsfp_coverage.py ../artifacts/fsfp-mcap/logs/ ../artifacts/fsfp-mcap/logs/
python3 fsfp_latency.py ../artifacts/fsfp-mcap/logs/ ../artifacts/fsfp-mcap/logs/
python3 fsfp_coverage.py ../artifacts/fsfp-mpow/logs/ ../artifacts/fsfp-mpow/logs/
python3 fsfp_latency.py ../artifacts/fsfp-mpow/logs/ ../artifacts/fsfp-mpow/logs/
python3 fsfp_coverage.py ../artifacts/fsfp-mprc/logs/ ../artifacts/fsfp-mprc/logs/
python3 fsfp_latency.py ../artifacts/fsfp-mprc/logs/ ../artifacts/fsfp-mprc/logs/
# Frame-spaced, tile-parallel
python3 fstp_coverage.py ../artifacts/fstp-base/logs/ ../artifacts/fstp-base/logs/
python3 fstp_latency.py ../artifacts/fstp-base/logs/ ../artifacts/fstp-base/logs/
python3 fstp_coverage.py ../artifacts/fstp-mcap/logs/ ../artifacts/fstp-mcap/logs/
python3 fstp_latency.py ../artifacts/fstp-mcap/logs/ ../artifacts/fstp-mcap/logs/
python3 fstp_coverage.py ../artifacts/fstp-mpow/logs/ ../artifacts/fstp-mpow/logs/
python3 fstp_latency.py ../artifacts/fstp-mpow/logs/ ../artifacts/fstp-mpow/logs/
python3 fstp_coverage.py ../artifacts/fstp-mprc/logs/ ../artifacts/fstp-mprc/logs/
python3 fstp_latency.py ../artifacts/fstp-mprc/logs/ ../artifacts/fstp-mprc/logs/
