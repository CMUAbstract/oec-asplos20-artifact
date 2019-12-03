# Scripts

This directory contains scripts.

## Directory Contents

* [collate_downlink_deficit.py](collate_downlink_deficit.py): Collates downlink
  deficit data logs into a CSV file
* [csfp_coverage.py](csfp_coverage.py): Collates close-spaced, frame-parallel
  data logs into a coverage CSV file
* [csfp_latency.py](csfp_latency.py): Collates close-spaced, frame-parallel
  data logs into a latency CSV file
* [cstp_coverage.py](cstp_coverage.py): Collates close-spaced, tile-parallel
  data logs into a coverage CSV file
* [cstp_latency.py](cstp_latency.py): Collates close-spaced, tile-parallel data
  logs into a latency CSV file
* [fsfp_coverage.py](fsfp_coverage.py): Collates frame-spaced, frame-parallel
  data logs into a coverage CSV file
* [fsfp_latency.py](fsfp_latency.py): Collates frame-spaced, frame-parallel
  data logs into a latency CSV file
* [fstp_coverage.py](fstp_coverage.py): Collates frame-spaced, tile-parallel
  data logs into a coverage CSV file
* [fstp_latency.py](fstp_latency.py): Collates frame-spaced, tile-parallel data
  logs into a latency CSV file
* [generate_f6_plots.sh](generate_f6_plots.sh): Generates downlink deficit plots
* [generate_f7_plots.sh](generate_f7_plots.sh): Generates latency plots
* [generate_f8_plots.sh](generate_f8_plots.sh): Generates coverage plots
* [generate_plots.sh](generate_plots.sh): Generates all plots
* [plot_f6a.py](plot_f6a.py): Plots orbit-spaced downlink deficits
* [plot_f6b.py](plot_f6b.py): Plots frame-spaced downlink deficits
* [plot_f6c.py](plot_f6c.py): Plots close-spaced downlink deficits
* [plot_f7a.py](plot_f7a.py): Plots close-spaced, tile-parallel latencies
* [plot_f7b.py](plot_f7b.py): Plots close-spaced, frame-parallel latencies
* [plot_f7c.py](plot_f7c.py): Plots frame-spaced, tile-parallel latencies
* [plot_f7d.py](plot_f7d.py): Plots frame-spaced, frame-parallel latencies
* [plot_f8a.py](plot_f8a.py): Plots close-spaced, tile-parallel coverage
* [plot_f8b.py](plot_f8b.py): Plots close-spaced, frame-parallel coverage
* [plot_f8c.py](plot_f8c.py): Plots frame-spaced, tile-parallel coverage
* [plot_f8d.py](plot_f8d.py): Plots frame-spaced, frame-parallel coverage
* [process_f6_logs.sh](process_f6_logs.sh): Calls Python scripts to generate
  downlink deficit logs
* [process_f7_f8_logs.sh](process_f7_f8_logs.sh): Calls all of the collation
  Python scripts in preparation for the latency plot Python scripts
* [process_logs.sh](process_logs.sh): Processes all of the logs
* [run_csfp_sims.sh](run_csfp_sims.sh): Run close-spaced, frame-parallel sims
* [run_cstp_sims.sh](run_cstp_sims.sh): Run close-spaced, tile-parallel sims
* [run_fsfp_sims.sh](run_fsfp_sims.sh): Run frame-spaced, frame-parallel sims
* [run_fstp_sims.sh](run_fstp_sims.sh): Run frame-spaced, tile-parallel sims
* [run_sims_cs.sh](run_sims_cs.sh): Run close-spaced communication sims
* [run_sims_fs.sh](run_sims_fs.sh): Run frame-spaced communication sims
* [run_sims_os.sh](run_sims_os.sh): Run orbit-spaced communication sims
* [setup_dependencies.sh](setup_dependencies.sh): Downloads and compiles GCC
  8.3.0 to the specified directory for use with the artifact software. The
  script path is expected to be `/home/username/sw`.
* [setup_py_venv.sh](setup_py_venv.sh): Sets up the Python virtual environment
  for Matplotlib
* [README.md](README.md): This document

## License

Copyright 2019 Bradley Denby

Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at <http://www.apache.org/licenses/LICENSE-2.0>.

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
