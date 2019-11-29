// Edge.hpp
// Edge class header file
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

#ifndef COMSIM_EDGE_HPP
#define COMSIM_EDGE_HPP

// Standard library
// None

// comsim
#include <Vertex.hpp> // Vertex

namespace comsim {
  class Edge {
  public:
    Edge(const Vertex* const src, const Vertex* const snk);
    Edge(const Edge& edge);
    Edge(Edge&& edge);
    virtual ~Edge();
    virtual Edge& operator=(const Edge& edge);
    virtual Edge& operator=(Edge&& edge);
    virtual Edge* clone() const;
    const Vertex* getSrc() const;
    const Vertex* getSnk() const;
  private:
    const Vertex* src;
    const Vertex* snk;
  };
}

#endif
