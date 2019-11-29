// ISim.hpp
// ISim interace file
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

#ifndef SATSIM_ISIM_HPP
#define SATSIM_ISIM_HPP

namespace satsim {
  class ISim {
  public:
    virtual void update(const double& seconds) = 0;
  };
}

#endif
