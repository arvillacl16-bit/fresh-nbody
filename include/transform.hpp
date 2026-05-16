#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "particle.hpp"

namespace fnb::transform {
  void inertial_to_jacobi_pos(const ParticleStore& particles, ParticleStore& p_j);
  void inertial_to_jacobi_vel(const ParticleStore& particles, ParticleStore& p_j);
  void inertial_to_jacobi_acc(const ParticleStore& particles, ParticleStore& p_j);
  void jacobi_to_inertial_pos(ParticleStore& particles, const ParticleStore& p_j);
  void jacobi_to_inertial_vel(ParticleStore& particles, const ParticleStore& p_j);
  void jacobi_to_inertial_acc(ParticleStore& particles, const ParticleStore& p_j);

  void inertial_to_demhelio_pos(const ParticleStore& particles, ParticleStore& p_h);
  void inertial_to_demhelio_vel(const ParticleStore& particles, ParticleStore& p_h);
  void inertial_to_demhelio_acc(const ParticleStore& particles, ParticleStore& p_h);
  void demhelio_to_inertial_pos(ParticleStore& particles, const ParticleStore& p_h);
  void demhelio_to_inertial_vel(ParticleStore& particles, const ParticleStore& p_h);
  void demhelio_to_inertial_acc(ParticleStore& particles, const ParticleStore& p_h);

  void inertial_to_whds_pos(const ParticleStore& particles, ParticleStore& p_h);
  void inertial_to_whds_vel(const ParticleStore& particles, ParticleStore& p_h);
  void inertial_to_whds_acc(const ParticleStore& particles, ParticleStore& p_h);
  void whds_to_inertial_pos(ParticleStore& particles, const ParticleStore& p_h);
  void whds_to_inertial_vel(ParticleStore& particles, const ParticleStore& p_h);
  void whds_to_inertial_acc(ParticleStore& particles, const ParticleStore& p_h);

  void inertial_to_barycentric_pos(const ParticleStore& particles, ParticleStore& p_b);
  void inertial_to_barycentric_vel(const ParticleStore& particles, ParticleStore& p_b);
  void inertial_to_barycentric_acc(const ParticleStore& particles, ParticleStore& p_b);
  void barycentric_to_inertial_pos(ParticleStore& particles, const ParticleStore& p_b);
  void barycentric_to_inertial_vel(ParticleStore& particles, const ParticleStore& p_b);
  void barycentric_to_inertial_acc(ParticleStore& particles, const ParticleStore& p_b);
} // namespace fnb::transform

#endif
