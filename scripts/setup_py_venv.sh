# setup_py_venv.sh
#
# A bash script that sets up a Python virtual environment with Matplotlib
#
# Usage: ./setup_py_venv.sh
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

python3 -m venv p3-env
source p3-env/bin/activate
python3 -m pip install matplotlib==3.1.2
deactivate
