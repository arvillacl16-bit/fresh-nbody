#include "integrator.hpp"
#include "particle.hpp"
#include "gravity.hpp"
#include <cstddef>

namespace fnb {
  void Leapfrog::step(ParticleStore& particles, double dt) {
    const size_t N = particles.N();

    auto& positions = particles.positions;
    auto& velocities = particles.velocities;
    auto& accelerations = particles.accelerations;

#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) particles.accelerations[i] = {0., 0., 0.};
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) positions[i] += velocities[i] * (dt / 2);
    
    switch (gravity) {
    case GravityMethod::BASIC:
      accel::basic(particles, epsilon * epsilon);
      break;
    case GravityMethod::COMPENSATED:
      accel::compensated(particles, epsilon * epsilon);
      break;
    case GravityMethod::JACOBI:
      accel::jacobi(particles, epsilon * epsilon);
      break;
    default:
      break;
    }

#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) velocities[i] += accelerations[i] * dt;
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) positions[i] += velocities[i] * (dt / 2);
  }
}
