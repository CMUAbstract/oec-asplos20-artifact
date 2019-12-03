// Edge.cpp
// Edge class implementation file
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
