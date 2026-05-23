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

  void inertial_to_jacobi_vel(const ParticleStore& particles, ParticleStore& p_j) {
    const size_t N = particles.N();
    const size_t N_thres = particles.test_thres().value_or(N);
    if (N < 2) return;

    Vec3 current_com_pos = particles.mus[0] * particles.positions[0];
    double current_tot_mass = particles.mus[0];
    for (size_t i = 1; i < N_thres; ++i) {
      p_j.velocities[i] = particles.velocities[i] - current_com_pos / current_tot_mass;

      current_com_pos += particles.mus[i] * particles.velocities[i];
      current_tot_mass += particles.mus[i];
    }

    if (N_thres < N) {
      current_com_pos += particles.mus[N_thres] * particles.velocities[N_thres];
      current_tot_mass += particles.mus[N_thres];
    }

    Vec3 act_com_pos = current_com_pos / current_tot_mass;
    for (size_t i = N_thres; i < N; ++i) {
      p_j.velocities[i] = particles.velocities[i] - act_com_pos;
    }

    p_j.velocities[0] = act_com_pos;
  }

  void inertial_to_jacobi_acc(const ParticleStore& particles, ParticleStore& p_j) {
    const size_t N = particles.N();
    const size_t N_thres = particles.test_thres().value_or(N);
    if (N < 2) return;

    Vec3 current_com_pos = particles.mus[0] * particles.positions[0];
    double current_tot_mass = particles.mus[0];
    for (size_t i = 1; i < N_thres; ++i) {
      p_j.accelerations[i] = particles.accelerations[i] - current_com_pos / current_tot_mass;

      current_com_pos += particles.mus[i] * particles.accelerations[i];
      current_tot_mass += particles.mus[i];
    }

    if (N_thres < N) {
      current_com_pos += particles.mus[N_thres] * particles.accelerations[N_thres];
      current_tot_mass += particles.mus[N_thres];
    }

    Vec3 act_com_pos = current_com_pos / current_tot_mass;
    for (size_t i = N_thres; i < N; ++i) {
      p_j.accelerations[i] = particles.accelerations[i] - act_com_pos;
    }

    p_j.accelerations[0] = act_com_pos;
  }

  void jacobi_to_inertial_pos(ParticleStore& particles, const ParticleStore& p_j) {
    const size_t N = particles.N();
    if (N < 2) return;

    const size_t N_thres = particles.test_thres().value_or(N);
    const Vec3 act_com_pos = p_j.positions[0];

    double total_chain_mass = p_j.mus[0];
    for (size_t i = 1; i < N_thres; ++i) {
      total_chain_mass += p_j.mus[i];
    }
    if (N_thres < N) {
      total_chain_mass += p_j.mus[N_thres];
    }

    double current_tot_mass = total_chain_mass;
    Vec3 current_com_pos = act_com_pos;

    for (size_t i = N_thres - 1; i > 0; --i) {
      double sub_mass = current_tot_mass - p_j.mus[i];

      particles.positions[i] = current_com_pos + (sub_mass / current_tot_mass) * p_j.positions[i];

      current_com_pos = current_com_pos - (p_j.mus[i] / current_tot_mass) * p_j.positions[i];
      current_tot_mass = sub_mass;
    }

    particles.positions[0] = current_com_pos;

#pragma omp parallel for schedule(static) if (N - N_thres > 64)
    for (size_t i = N_thres; i < N; ++i) {
      particles.positions[i] = p_j.positions[i] + act_com_pos;
    }
  }

  void jacobi_to_inertial_vel(ParticleStore& particles, const ParticleStore& p_j) {
    const size_t N = particles.N();
    if (N < 2) return;

    const size_t N_thres = particles.test_thres().value_or(N);
    const Vec3 act_com_pos = p_j.velocities[0];

    double total_chain_mass = p_j.mus[0];
    for (size_t i = 1; i < N_thres; ++i) {
      total_chain_mass += p_j.mus[i];
    }
    if (N_thres < N) {
      total_chain_mass += p_j.mus[N_thres];
    }

    double current_tot_mass = total_chain_mass;
    Vec3 current_com_pos = act_com_pos;

    for (size_t i = N_thres - 1; i > 0; --i) {
      double sub_mass = current_tot_mass - p_j.mus[i];

      particles.velocities[i] = current_com_pos + (sub_mass / current_tot_mass) * p_j.velocities[i];

      current_com_pos = current_com_pos - (p_j.mus[i] / current_tot_mass) * p_j.velocities[i];
      current_tot_mass = sub_mass;
    }

    particles.velocities[0] = current_com_pos;

#pragma omp parallel for schedule(static) if (N - N_thres > 64)
    for (size_t i = N_thres; i < N; ++i) {
      particles.velocities[i] = p_j.velocities[i] + act_com_pos;
    }
  }

  void inertial_to_demhelio_pos(const ParticleStore& particles, ParticleStore& p_h) {
    p_h.positions[0] = [&](){
      Vec3 bary;
      double total_mu = 0;
#pragma omp parallel for reduction (+:bary, total_mu)
      for (size_t i = 0; i < particles.test_thres().value_or(particles.N()); ++i) {
        bary += particles.mus[i] * particles.positions[i];
        total_mu += particles.mus[i];
      }

      bary /= total_mu;
      return bary;
    }();
#pragma omp parallel for
    for (size_t i = 1; i < particles.N(); ++i) p_h.positions[i] = particles.positions[i] - particles.positions[0];
  }

  void inertial_to_demhelio_vel(const ParticleStore& particles, ParticleStore& p_h) {
    double star_mu = particles.mus[0];

    Vec3 total_momentum;
    double total_mu = 0;
#pragma omp parallel for reduction (+:total_momentum, total_mu)
    for (size_t i = 0; i < particles.test_thres().value_or(particles.N()); ++i) { 
      total_momentum += particles.mus[i] * particles.velocities[i]; 
      total_mu += particles.mus[i];
    }

    p_h.velocities[0] = total_momentum / total_mu;

#pragma omp parallel for
    for (size_t i = 1; i < particles.N(); ++i) p_h.velocities[i] = particles.velocities[i] - particles.velocities[0];
  }
} // namespace fnb::transform
