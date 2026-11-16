// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COLLISIONS_HPP_
#define COLLISIONS_HPP_

#include "particle.hpp"
#include <functional>
#include <variant>

namespace fnb {
  enum class CollisionType : uint8_t { NONE, BASIC };
  enum class CollisionResult : uint8_t { P1, P2, BOTH };

  void update_particles_basic_collision(ParticleStore& particles, const std::function<CollisionResult(ParticleStore&, size_t, size_t)>& callback);
}

#endif
