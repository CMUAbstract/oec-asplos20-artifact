# Scripts

This directory contains scripts.

## Directory Contents

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
* [generate_f7_plots.sh](generate_f7_plots.sh): Generates latency plots
* [generate_f8_plots.sh](generate_f8_plots.sh): Generates coverage plots
* [plot_f7a.py](plot_f7a.py): Plots close-spaced, tile-parallel latencies
* [plot_f7b.py](plot_f7b.py): Plots close-spaced, frame-parallel latencies
* [plot_f7c.py](plot_f7c.py): Plots frame-spaced, tile-parallel latencies
* [plot_f7d.py](plot_f7d.py): Plots frame-spaced, frame-parallel latencies
* [plot_f8a.py](plot_f8a.py): Plots close-spaced, tile-parallel coverage
* [plot_f8b.py](plot_f8b.py): Plots close-spaced, frame-parallel coverage
* [plot_f8c.py](plot_f8c.py): Plots frame-spaced, tile-parallel coverage
* [plot_f8d.py](plot_f8d.py): Plots frame-spaced, frame-parallel coverage
* [process_f7_f8_logs.sh](process_f7_f8_logs.sh): Calls all of the collation
  Python scripts in preparation for the latency plot Python scripts
* [setup_dependencies.sh](setup_dependencies.sh): Downloads and compiles GCC
  8.3.0 to the specified directory for use with the artifact software. The
  script path is expected to be `/home/username/sw`.
* [setup_py_venv.sh](setup_py_venv.sh): Sets up the Python virtual environment
  for Matplotlib
* [README.md](README.md): This document

## License

Written by Bradley Denby  
Other contributors: None

To the extent possible under law, the author(s) have dedicated all copyright and
related and neighboring rights to this work to the public domain worldwide. This
work is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication with this
work. If not, see <https://creativecommons.org/publicdomain/zero/1.0/>.
