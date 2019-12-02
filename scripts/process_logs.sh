#!/bin/bash
#
# process_logs.sh
# A bash script that collates the logs
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

./process_f6_logs.sh
./process_f7_f8_logs.sh
echo "Log processing complete."
