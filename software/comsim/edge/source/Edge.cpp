// Edge.cpp
// Edge class implementation file
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
#include <cstddef>    // NULL
#include <utility>    // move

// comsim
#include <Edge.hpp>   // Edge
#include <Vertex.hpp> // Vertex

namespace comsim {
  Edge::Edge(const Vertex* const src, const Vertex* const snk) :
   src(src), snk(snk) {}

  Edge::Edge(const Edge& edge) : src(edge.getSrc()),  snk(edge.getSnk()) {}

  Edge::Edge(Edge&& edge) : src(edge.src),  snk(edge.snk) {
    edge.src = NULL;
    edge.snk = NULL;
  }

  Edge::~Edge() {
    this->src = NULL;
    this->snk = NULL;
  }

  Edge& Edge::operator=(const Edge& edge) {
    Edge temp(edge);
    *this = std::move(temp);
    return *this;
  }

  Edge& Edge::operator=(Edge&& edge) {
    this->src = edge.src;
    this->snk = edge.snk;
    edge.src = NULL;
    edge.snk = NULL;
    return *this;
  }

  Edge* Edge::clone() const {
    return new Edge(*this);
  }

  const Vertex* Edge::getSrc() const {
    return this->src;
  }

  const Vertex* Edge::getSnk() const {
    return this->snk;
  }
}
