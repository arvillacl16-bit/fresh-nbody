#include "integrator.hpp"
#include "particle.hpp"
#include "gravity.hpp"
#include <cstddef>

namespace fnb {
  void Leapfrog::step(ParticleStore& particles, ParticleStore& particles_test, double dt) {
    const size_t N = particles.N();
    const size_t N_test = particles_test.N();

    auto& positions = particles.positions;
    auto& velocities = particles.velocities;
    auto& accelerations = particles.accelerations;

    auto& positions_test = particles_test.positions;
    auto& velocities_test = particles_test.velocities;
    auto& accelerations_test = particles_test.accelerations;

#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) particles.accelerations[i] = {0., 0., 0.};
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) positions[i] += velocities[i] * (dt / 2);
#pragma omp parallel for
    for (size_t i = 0; i < N_test; ++i) positions_test[i] += velocities_test[i] * (dt / 2);
    
    accel::basic(particles, particles_test);

#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) velocities[i] += accelerations[i] * dt;
#pragma omp parallel for
    for (size_t i = 0; i < N_test; ++i) velocities_test[i] += accelerations_test[i] * dt;
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) positions[i] += velocities[i] * (dt / 2);
#pragma omp parallel for
    for (size_t i = 0; i < N_test; ++i) positions_test[i] += velocities_test[i] * (dt / 2);
  }
}
