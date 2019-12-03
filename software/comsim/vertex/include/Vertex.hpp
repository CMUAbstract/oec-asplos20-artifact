// Vertex.hpp
// Vertex class header file
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
