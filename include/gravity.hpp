#ifndef GRAVITY_HPP_
#define GRAVITY_HPP_

#include "particle.hpp"
namespace fnb::accel {
  void basic(ParticleStore& particles, double epsilon2);
  void jacobi(ParticleStore& particles, double epsilon2);
  void compensated(ParticleStore& particles, double epsilon2);
}

#endif
