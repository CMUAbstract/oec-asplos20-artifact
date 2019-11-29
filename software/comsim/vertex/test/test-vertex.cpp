// test-vertex.cpp
// Vertex class test file
//
// Written by Bradley Denby
// Other contributors: None
//
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication with this
// software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Standard library
#include <cstdlib>    // exit, EXIT_SUCCESS
#include <iostream>   // cout
#include <ostream>    // endl

// comsim
#include <Vertex.hpp> // Vertex

int main(int argc, char** argv) {
  std::cout << "Test: Vertex constructor"
            << std::endl;
  comsim::Vertex vertex;
  std::cout << "  Success"
            << std::endl;
  std::cout << "Test: Vertex clone"
            << std::endl; 
  comsim::Vertex* vertexClone = vertex.clone();
  std::cout << "  Success"
            << std::endl;
  delete vertexClone;
  std::cout << "Vertex tests complete"
            << std::endl;
  std::exit(EXIT_SUCCESS);
}
