// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GRAVITY_HPP_
#define GRAVITY_HPP_

#include "particle.hpp"
namespace fnb::accel {
  void basic(ParticleStore& particles, double epsilon2);
  void jacobi(ParticleStore& particles, double epsilon2);
  void compensated(ParticleStore& particles, double epsilon2);
} // namespace fnb::accel

#endif
