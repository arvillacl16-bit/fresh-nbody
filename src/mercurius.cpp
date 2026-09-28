// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "integrator.hpp"
#include "particle.hpp"
#include "transform.hpp"

namespace fnb {
  void Mercurius::step(ParticleStore& particles, double dt) {
    if (auto n = particles.N() - p_h_.N(); n > 0) {
      for (size_t i = 0; i < n; ++i) particles.add_particle(IndParticle{});
    }

    transform::inertial_to_demhelio_pos(particles, p_h_);
    transform::inertial_to_demhelio_vel(particles, p_h_);

    //
    
    transform::demhelio_to_inertial_pos(particles, p_h_);
    transform::demhelio_to_inertial_vel(particles, p_h_);
  }
} // namespace fnb
