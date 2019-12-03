#!/bin/bash
#
# run_cstp_sims.sh
# A bash script that runs the close-spaced, tile-parallel simulations
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

cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-base/scripts/
./run_cstp_base_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-mcap/scripts/
./run_cstp_mcap_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-mpow/scripts/
./run_cstp_mpow_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-mprc/scripts/
./run_cstp_mprc_sims.sh
echo "CSTP simulations are running in the background."
echo "It may be awhile before they complete, check with 'top'."
