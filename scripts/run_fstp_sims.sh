#!/bin/bash
#
# run_fstp_sims.sh
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

cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fstp-base/scripts/
./run_fstp_base_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fstp-mcap/scripts/
./run_fstp_mcap_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fstp-mpow/scripts/
./run_fstp_mpow_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fstp-mprc/scripts/
./run_fstp_mprc_sims.sh
echo "FSTP simulations are running in the background."
echo "It may be awhile before they complete, check with 'top'."
