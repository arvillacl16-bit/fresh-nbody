#include "gravity.hpp"
#include <cstddef>

namespace fnb::accel {
  void basic(ParticleStore& particles, ParticleStore& particles_test) {
    const size_t N = particles.N();
    const size_t N_test = particles_test.N();

    auto& positions = particles.positions;
    auto& accelerations = particles.accelerations;
    auto& mus = particles.mus;

    auto& positions_test = particles_test.positions;
    auto& accelerations_test = particles_test.accelerations;

    for (size_t i = 0; i < N; ++i) {
      for (size_t j = i + 1; j < N; ++j) {
        Vec3 dp = positions[i] - positions[j];
        double r = dp.mag(); 
        double inv_r3 =  1. / (r * r * r);
        accelerations[j] = dp * (mus[i] * inv_r3);
        accelerations[i] = -dp * (mus[j] * inv_r3);
      }

      for (size_t j = 0; j < N_test; ++j) {
        Vec3 dp = positions[i] - positions_test[j];
        double r = dp.mag();
        double inv_r3 = 1. / (r * r * r);
        accelerations_test[j] = dp * (mus[i] * inv_r3);
      }
    }
  }
}
