// Edge.hpp
// Edge class header file
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
