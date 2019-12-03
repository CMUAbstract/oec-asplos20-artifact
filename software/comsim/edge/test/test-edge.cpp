// test-edge.cpp
// Edge class test file
//
// Copyright 2019 Bradley Denby
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at <http://www.apache.org/licenses/LICENSE-2.0>.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// Standard library
#include <cstdlib>    // exit, EXIT_SUCCESS
#include <iostream>   // cout
#include <ostream>    // endl

// comsim
#include <Edge.hpp>   // Edge
#include <Vertex.hpp> // Vertex

int main(int argc, char** argv) {
  comsim::Vertex src;
  comsim::Vertex snk;
  std::cout << "Test: Edge constructor"
            << std::endl;
  comsim::Edge edge(&src, &snk);
  std::cout << "  Success"
            << std::endl;
  std::cout << "Test: Edge clone"
            << std::endl; 
  comsim::Edge* edgeClone = edge.clone();
  std::cout << "  Success"
            << std::endl;
  delete edgeClone;
  std::cout << "Edge tests complete"
            << std::endl;
  std::exit(EXIT_SUCCESS);
}
