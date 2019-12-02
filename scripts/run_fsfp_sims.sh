#!/bin/bash
#
# run_fsfp_sims.sh
# A bash script that runs the close-spaced, frame-parallel simulations
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

cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fsfp-base/scripts/
./run_fsfp_base_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fsfp-mcap/scripts/
./run_fsfp_mcap_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fsfp-mpow/scripts/
./run_fsfp_mpow_sims.sh
cd $HOME/git-repos/oec-asplos20-artifact/artifacts/fsfp-mprc/scripts/
./run_fsfp_mprc_sims.sh
echo "FSFP simulations are running in the background."
echo "It may be awhile before they complete, check with 'top'."
