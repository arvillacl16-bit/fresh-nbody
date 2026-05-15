#include "transform.hpp"
#include "particle.hpp"
#include <cstddef>

namespace fnb::transform {
  void inertial_to_jacobi_pos(const ParticleStore& particles, ParticleStore& p_j) {
    const size_t N = particles.N();
    const size_t N_thres = particles.test_thres().value_or(N);
    if (N < 2) return;

    Vec3 current_com_pos = particles.mus[0] * particles.positions[0];
    double current_tot_mass = particles.mus[0];
    for (size_t i = 1; i < N_thres; ++i) {
      p_j.positions[i] = particles.positions[i] - current_com_pos / current_tot_mass;

      current_com_pos += particles.mus[i] * particles.positions[i];
      current_tot_mass += particles.mus[i];
    }

    if (N_thres < N) {
      current_com_pos += particles.mus[N_thres] * particles.positions[N_thres];
      current_tot_mass += particles.mus[N_thres];
    }

    Vec3 act_com_pos = current_com_pos / current_tot_mass;
    for (size_t i = N_thres; i < N; ++i) {
      p_j.positions[i] = particles.positions[i] - act_com_pos;
    }

    p_j.positions[0] = act_com_pos;
  }

  void jacobi_to_inertial_pos(ParticleStore& particles, const ParticleStore& p_j) {
    const size_t N = particles.N();
    const size_t N_thres = particles.test_thres().value_or(N - 1);
    if (N < 2) return;
    double M = 0;
#pragma omp parallel for reduction(+ : M)
    for (size_t i = 1; i < N; ++i) M += p_j.mus[i];
    Vec3 R_pos = p_j.positions[0] * M;
    for (size_t i = N - 1; i > N_thres; --i) {
      particles.positions[i] = p_j.positions[i] + R_pos / M;
    }
    for (size_t i = N_thres; i > 0; --i) {
      R_pos = (R_pos + p_j.mus[i] * p_j.positions[i]) / M;
      particles.positions[i] += R_pos;
      M -= p_j.mus[i];
      R_pos *= M;
    }
    particles.positions[0] = R_pos / p_j.mus[0];
  }
} // namespace fnb::transform
