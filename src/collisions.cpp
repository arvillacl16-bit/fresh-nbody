// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "collisions.hpp"
#include "particle.hpp"

namespace fnb {
  void update_particles_basic_collision(ParticleStore& particles, const std::function<CollisionResult(size_t, size_t)>& f) {
    size_t N = particles.N();
    std::vector<size_t> results;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = i + 1; j < N; ++j) {
        double d2 = particles.positions[i].dist2(particles.positions[j]);
        if (d2 < particles.radii[i] + particles.radii[j]) {
          auto coll_res = f(i, j);
          if (coll_res == CollisionResult::BOTH) {
            results.push_back(i);
            results.push_back(j);
          } else if (coll_res == CollisionResult::P1) results.push_back(i);
          else results.push_back(j);
        }
      }
    }

    for (size_t i : results) particles.positions[i] = {NAN, NAN, NAN};
    for (size_t i = N - 1; i-- > 0;) {
       if (particles.positions[i].x == NAN) particles.remove_particle(i);
    }
  }
}
