#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "particle.hpp"

namespace fnb::transform {
  void inertial_to_jacobi_pv(const ParticleStore& particles, ParticleStore& p_j);
  void inertial_to_jacobi_pva(const ParticleStore& particles, ParticleStore& p_j);
  void inertial_to_jacobi_a(const ParticleStore& particles, ParticleStore& p_j);

  void jacobi_to_inertial_pv(ParticleStore& particles, const ParticleStore& p_j);
  void jacobi_to_inertial_p(ParticleStore& particles, const ParticleStore& p_j);
  void jacobi_to_inertial_a(ParticleStore& particles, const ParticleStore& p_j);

  void inertial_to_demhelio_pv(const ParticleStore& particles, ParticleStore& p_h);
  void demhelio_to_inertial_p(ParticleStore& particles, const ParticleStore& p_h);
  void demhelio_to_inertial_pv(ParticleStore& particles, const ParticleStore& p_h);

  void inertial_to_whds_pv(const ParticleStore& particles, ParticleStore& p_h);
  void whds_to_inertial_p(ParticleStore& particles, const ParticleStore& p_h);
  void whds_to_inertial_pv(ParticleStore& particles, const ParticleStore& p_h);

  void inertial_to_barycentric_pv(const ParticleStore& particles, ParticleStore& p_b);
  void inertial_to_barycentric_a(const ParticleStore& particles, ParticleStore& p_b);
  void barycentric_to_inertial_p(ParticleStore& particles, const ParticleStore& p_b);
  void barycentric_to_inertial_pv(ParticleStore& particles, const ParticleStore& p_b);
  void barycentric_to_inertial_a(ParticleStore& particles, const ParticleStore& p_b);
} // namespace fnb::transform

#endif
