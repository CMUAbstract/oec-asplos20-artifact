# Orbital Edge Computing ASPLOS 2020 Artifact Software

This software artifact simulates orbital edge computing scenarios. See [Orbital Edge Computing: Nanosatellite Constellations as a New Class of Computer System](https://abstract.ece.cmu.edu/pubs/oec-asplos2020.pdf) for information on this project.

**Current version**: 1.0.0

* This software uses [semantic versioning](http://semver.org).

**Dependencies**

* C++11 and C++17 compilers ([install script](scripts/setup_dependencies.sh))
* CMake for building Makefiles (user must install separately)
* Standard command line tools (e.g. make, wget)
* Python 3 with the `venv` module (virtual environment used for plotting)

```bash
sudo apt install make git build-essential cmake
sudo apt install python3-dev python3-pip python3-tk python3-venv
```

## Directory Contents

* [artifacts](artifacts/README.md): Artifact programs
* [plots](plots/README.md): Destination directory for artifact plots
* [scripts](scripts/README.md): Useful scripts, e.g. for setting up dependencies
* [software](software/README.md): Classes, utilities, etc.
* [README.md](README.md): This document

## How to Use

Clone the repository into the specified location.

```bash
mkdir $HOME/git-repos
cd $HOME/git-repos
git clone https://github.com/CMUAbstract/oec-asplos20-artifact.git
```

Change directories to the top-level `scripts` directory:

```bash
cd $HOME/git-repos/oec-asplos20-artifact/scripts/
```

Run the dependency setup script. This script downloads GCC 8.3.0 and compiles it
for use. Ensure that the host system has essential build tools installed.

```bash
./setup_dependencies.sh $HOME/sw
```

Launch the CSFP simulations (68 processes). A 48+ core machine is recommended.
Memory usage should remain low. The simulations will produce over 135,000 log
files occupying 65.0 MB+ of total disk space. Recommendation: wait for these
simulations to complete before proceeding.

```bash
./run_csfp_sims.sh
```

Launch the CSTP simulations (68 processes). A 48+ core machine is recommended.
Memory usage may be moderate to low. The simulations will produce over 2,000,000
log files occupying over 1.5 GB of total disk space. Recommendation: wait for
these simulations to complete before proceeding.

```bash
./run_cstp_sims.sh
```

Launch the FSFP simulations (68 processes). A 48+ core machine is recommended.
Memory usage should remain low. The simulations will produce over 135,000 log
files occupying 65.0 MB+ of total disk space. Recommendation: wait for these
simulations to complete before proceeding.

```bash
./run_fsfp_sims.sh
```

Launch the FSTP simulations (68 processes). A 48+ core machine is recommended.
Memory usage may be moderate to low. The simulations will produce over 2,000,000
log files occupying over 1.5 GB of total disk space. Recommendation: wait for
these simulations to complete before proceeding.

```bash
./run_fstp_sims.sh
```

Launch the CS simulations. A 48+ core machine is recommended. Memory usage
should remain low. The simulations will produce over 13,000 log files occupying
over 6.0 GB of total disk space. Recommendation: wait for these simulations to
complete before proceeding.

```bash
./run_sims_cs.sh
```

Launch the FS simulations. A 48+ core machine is recommended. Memory usage
should remain low. The simulations will produce over 13,000 log files occupying
over 6.0 GB of total disk space. Recommendation: wait for these simulations to
complete before proceeding.

```bash
./run_sims_fs.sh
```

Launch the OS simulations. A 48+ core machine is recommended. Memory usage
should remain low. The simulations will produce over 13,000 log files occupying
over 7.0 GB of total disk space. Recommendation: wait for these simulations to
complete before proceeding.

```bash
./run_sims_os.sh
```

Process the data logs. Data log processing may take some time.

```bash
./process_logs.sh
```

Set up the Python virtual environment used for generating plots.

```bash
./setup_py_venv.sh
```

Generate the plots.

```bash
./generate_plots.sh
```

## License

Copyright 2019 Bradley Denby

Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at <http://www.apache.org/licenses/LICENSE-2.0>.

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
