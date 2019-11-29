// Vertex.cpp
// Vertex class implementation file
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
// None

// comsim
#include <Vertex.hpp> // Vertex

namespace comsim {
  Vertex::Vertex() {}

  Vertex* Vertex::clone() const {
    return new Vertex(*this);
  }
}
