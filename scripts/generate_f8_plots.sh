#!/bin/bash
#
# generate_f8_plots.sh
# A bash script that generates the latency plots
#
# Usage: ./generate_f8_plots.sh
# Arguments: None; assumes execution from the top-level scripts directory.
# Outputs: Latency plot files
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

source p3-env/bin/activate
python3 plot_f8a.py ../artifacts/ ../plots/
python3 plot_f8b.py ../artifacts/ ../plots/
python3 plot_f8c.py ../artifacts/ ../plots/
python3 plot_f8d.py ../artifacts/ ../plots/
deactivate
