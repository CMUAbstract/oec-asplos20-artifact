#!/bin/bash
#
# run_csfp_sims.sh
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

../artifacts/csfp-base/scripts/run_csfp_base_sims.sh
../artifacts/csfp-mcap/scripts/run_csfp_mcap_sims.sh
../artifacts/csfp-mpow/scripts/run_csfp_mpow_sims.sh
../artifacts/csfp-mprc/scripts/run_csfp_mprc_sims.sh
echo "CSFP simulations are running in the background."
echo "It may be awhile before they complete, check with 'top'."
