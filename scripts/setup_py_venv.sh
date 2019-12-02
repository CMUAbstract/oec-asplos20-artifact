# setup_py_venv.sh
#
# A bash script that sets up a Python virtual environment with Matplotlib
#
# Usage: ./setup_py_venv.sh
#
# Written by Bradley Denby  
# Other contributors: None
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this work to the public domain
# worldwide. This work is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication with this
# work. If not, see <https://creativecommons.org/publicdomain/zero/1.0/>.

python3 -m venv p3-env
source p3-env/bin/activate
python3 -m pip install matplotlib==3.1.2
deactivate
