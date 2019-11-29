// Vertex.hpp
// Vertex class header file
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

#ifndef COMSIM_VERTEX_HPP
#define COMSIM_VERTEX_HPP

// Standard library
// None

// comsim
// None

namespace comsim {
  class Vertex {
  public:
    Vertex();
    Vertex(const Vertex& vertex) = default;
    Vertex(Vertex&& vertex) = default;
    virtual ~Vertex() = default;
    virtual Vertex& operator=(const Vertex& vertex) = default;
    virtual Vertex& operator=(Vertex&& vertex) = default;
    virtual Vertex* clone() const;
  };
}

#endif
