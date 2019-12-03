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
