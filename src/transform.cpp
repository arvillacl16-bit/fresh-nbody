#include "transform.hpp"
#include "particle.hpp"
#include <cstddef>

namespace fnb::transform {
  void inertial_to_jacobi_pv(const ParticleStore& particles, ParticleStore& p_j) {
    const size_t N = particles.N();
    const size_t N_thres = particles.test_thres().value_or(N);
    Vec3 current_com_pos = particles.mus[0] * particles.positions[0];
    Vec3 current_com_vel = particles.mus[0] * particles.velocities[0];
    double current_tot_mass = particles.mus[0];
    p_j.positions[0] = particles.positions[1] - current_com_pos / current_tot_mass;
    p_j.velocities[0] = particles.velocities[1] - current_com_vel / current_tot_mass;
    for (size_t i = 1; i < N_thres; ++i) {
      p_j.positions[i] = particles.positions[i + 1] - current_com_pos / current_tot_mass;
      p_j.velocities[i] = particles.velocities[i + 1] - current_com_vel / current_tot_mass;

      current_com_pos += particles.mus[i] * particles.positions[i];
      current_com_vel += particles.mus[i] * particles.velocities[i];
      current_tot_mass += particles.mus[i];
    }

    Vec3 act_com_pos = current_com_pos / current_tot_mass;
    Vec3 act_com_vel = current_com_vel / current_tot_mass;
    for (size_t i = N_thres; i < N; ++i) {
      p_j.positions[i] = particles.positions[i] - act_com_pos;
      p_j.velocities[i] = particles.velocities[i] - act_com_vel;
    }
  }

  void inertial_to_jacobi_pva(const ParticleStore& particles, ParticleStore& p_j) {
    const size_t N = particles.N();
    const size_t N_thres = particles.test_thres().value_or(N);
    Vec3 current_com_pos = particles.mus[0] * particles.positions[0];
    Vec3 current_com_vel = particles.mus[0] * particles.velocities[0];
    Vec3 current_com_acc = particles.mus[0] * particles.accelerations[0];
    double current_tot_mass = particles.mus[0];
    p_j.positions[0] = particles.positions[1] - current_com_pos / current_tot_mass;
    p_j.velocities[0] = particles.velocities[1] - current_com_vel / current_tot_mass;
    p_j.accelerations[0] = particles.accelerations[1] - current_com_acc / current_tot_mass;
    for (size_t i = 1; i < N_thres; ++i) {
      p_j.positions[i] = particles.positions[i + 1] - current_com_pos / current_tot_mass;
      p_j.velocities[i] = particles.velocities[i + 1] - current_com_vel / current_tot_mass;
      p_j.accelerations[i] = particles.accelerations[i + 1] - current_com_acc / current_tot_mass;

      current_com_pos += particles.mus[i] * particles.positions[i];
      current_com_vel += particles.mus[i] * particles.velocities[i];
      current_com_acc += particles.mus[i] * particles.accelerations[i];
      current_tot_mass += particles.mus[i];
    }

    Vec3 act_com_pos = current_com_pos / current_tot_mass;
    Vec3 act_com_vel = current_com_vel / current_tot_mass;
    Vec3 act_com_acc = current_com_acc / current_tot_mass;
    for (size_t i = N_thres; i < N; ++i) {
      p_j.positions[i] = particles.positions[i] - act_com_pos;
      p_j.velocities[i] = particles.velocities[i] - act_com_vel;
      p_j.accelerations[i] = particles.accelerations[i] - act_com_acc;
    }
  }

  void inertial_to_jacobi_a(const ParticleStore& particles, ParticleStore& p_j) {
    const size_t N = particles.N();
    const size_t N_thres = particles.test_thres().value_or(N);
    Vec3 current_com_acc = particles.mus[0] * particles.accelerations[0];
    double current_tot_mass = particles.mus[0];
    p_j.accelerations[0] = particles.accelerations[1] - current_com_acc / current_tot_mass;
    for (size_t i = 1; i < N_thres; ++i) {
      p_j.accelerations[i] = particles.accelerations[i + 1] - current_com_acc / current_tot_mass;
      current_com_acc += particles.mus[i] * particles.accelerations[i];
      current_tot_mass += particles.mus[i];
    }

    Vec3 act_com_acc = current_com_acc / current_tot_mass;
    for (size_t i = N_thres; i < N; ++i) {
      p_j.accelerations[i] = particles.accelerations[i] - act_com_acc;
    }
  }
}
