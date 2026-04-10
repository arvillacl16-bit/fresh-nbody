#include "gravity.hpp"
#include "particle.hpp"
#include <cassert>
#include <cstddef>

namespace fnb::accel {
  void basic(ParticleStore& particles, double epsilon2) {
    const size_t N = particles.N();
    const size_t test_thres = particles.positions.test_thres() ? particles.positions.test_thres().get() : N;

    auto& positions = particles.positions;
    auto& accelerations = particles.accelerations;
    auto& mus = particles.mus;

    for (size_t i = 0; i < test_thres; ++i) {
      for (size_t j = i + 1; j < test_thres; ++j) {
        Vec3 dp = positions[i] - positions[j];
        double r = dp.mag();
        double inv_r3 = 1. / (r * (dp.mag2() + epsilon2));
        accelerations[j] += dp * (mus[i] * inv_r3);
        accelerations[i] -= dp * (mus[j] * inv_r3);
      }

      for (size_t j = test_thres; j < N; ++j) {
        Vec3 dp = positions[i] - positions[j];
        double r = dp.mag();
        double inv_r3 = 1. / (r * (dp.mag2() + epsilon2));
        accelerations[j] += dp * (mus[i] * inv_r3);
      }
    }
  }

  void compensated(ParticleStore& particles, double epsilon2) {
    const size_t N = particles.N();
    const size_t test_thres = particles.positions.test_thres() ? particles.positions.test_thres().get() : N;

    auto& positions = particles.positions;
    auto& accelerations = particles.accelerations;
    auto& mus = particles.mus;

    for (size_t i = 0; i < N; ++i) {
      Vec3 sum;
      Vec3 c;
      for (size_t j = 0; j < test_thres; ++j) {
        if (i == j) continue;

        Vec3 dp = positions[i] - positions[j];
        double r = dp.mag();
        double inv_r3 = 1. / (r * (dp.mag2() + epsilon2));
        Vec3 opp_force = dp * (mus[j] * inv_r3);

        Vec3 y = opp_force - c;
        Vec3 t = sum + y;
        c = (t - sum) - y;
        sum = t;
      }

      accelerations[i] = -sum;
    }
  }

  void jacobi(ParticleStore& particles, double epsilon2) {
    //
  }
} // namespace fnb::accel
