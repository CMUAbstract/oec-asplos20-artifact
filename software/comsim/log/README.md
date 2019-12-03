# Log Singleton

The `Log` singleton acts as a central object for all event and measurement logs.
It is responsible for writing logs to storage, either when a log becomes too
long or upon request.

## Directory Contents

* [build](build/README.md): Compile and run the test program
* [include](include/Log.hpp): Header files
* [source](source/Log.cpp): Implementation files
* [test](test/test-log.cpp): Test program
* [README.md](README.md): This document

## License

Copyright 2019 Bradley Denby

Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at <http://www.apache.org/licenses/LICENSE-2.0>.

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
