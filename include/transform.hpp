#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "particle.hpp"

namespace fnb::transform {
  void inertial_to_jacobi_pos(const ParticleStore& restrict particles, ParticleStore& restrict p_j);
  void inertial_to_jacobi_vel(const ParticleStore& restrict particles, ParticleStore& restrict p_j);
  void inertial_to_jacobi_acc(const ParticleStore& restrict particles, ParticleStore& restrict p_j);
  void jacobi_to_inertial_pos(ParticleStore& restrict particles, const ParticleStore& restrict p_j);
  void jacobi_to_inertial_vel(ParticleStore& restrict particles, const ParticleStore& restrict p_j);
  void jacobi_to_inertial_acc(ParticleStore& restrict particles, const ParticleStore& restrict p_j);

  void inertial_to_demhelio_pos(const ParticleStore& restrict particles, ParticleStore& restrict p_h);
  void inertial_to_demhelio_vel(const ParticleStore& restrict particles, ParticleStore& restrict p_h);
  void inertial_to_demhelio_acc(const ParticleStore& restrict particles, ParticleStore& restrict p_h);
  void demhelio_to_inertial_pos(ParticleStore& restrict particles, const ParticleStore& restrict p_h);
  void demhelio_to_inertial_vel(ParticleStore& restrict particles, const ParticleStore& restrict p_h);
  void demhelio_to_inertial_acc(ParticleStore& restrict particles, const ParticleStore& restrict p_h);

  void inertial_to_whds_pos(const ParticleStore& restrict particles, ParticleStore& restrict p_h);
  void inertial_to_whds_vel(const ParticleStore& restrict particles, ParticleStore& restrict p_h);
  void inertial_to_whds_acc(const ParticleStore& restrict particles, ParticleStore& restrict p_h);
  void whds_to_inertial_pos(ParticleStore& restrict particles, const ParticleStore& restrict p_h);
  void whds_to_inertial_vel(ParticleStore& restrict particles, const ParticleStore& restrict p_h);
  void whds_to_inertial_acc(ParticleStore& restrict particles, const ParticleStore& restrict p_h);

  void inertial_to_barycentric_pos(const ParticleStore& restrict particles, ParticleStore& restrict p_b);
  void inertial_to_barycentric_vel(const ParticleStore& restrict particles, ParticleStore& restrict p_b);
  void inertial_to_barycentric_acc(const ParticleStore& restrict particles, ParticleStore& restrict p_b);
  void barycentric_to_inertial_pos(ParticleStore& restrict particles, const ParticleStore& restrict p_b);
  void barycentric_to_inertial_vel(ParticleStore& restrict particles, const ParticleStore& restrict p_b);
  void barycentric_to_inertial_acc(ParticleStore& restrict particles, const ParticleStore& restrict p_b);
} // namespace fnb::transform

#endif
