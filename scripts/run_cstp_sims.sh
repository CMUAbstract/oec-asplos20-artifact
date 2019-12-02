#!/bin/bash
#
# run_cstp_sims.sh
# A bash script that runs the close-spaced, tile-parallel simulations
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

cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-base/scripts/
./run_cstp_base_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-mcap/scripts/
./run_cstp_mcap_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-mpow/scripts/
run_cstp_mpow_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/cstp-mprc/scripts/
./run_cstp_mprc_sims.sh
echo "CSTP simulations are running in the background."
echo "It may be awhile before they complete, check with 'top'."
