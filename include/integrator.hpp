#ifndef INTEGRATOR_HPP_
#define INTEGRATOR_HPP_

#include "particle.hpp"
#include <cstdint>

namespace fnb {
  enum class GravityMethod : uint8_t { BASIC };
  
  class Leapfrog {
  public:
    GravityMethod gravity = GravityMethod::BASIC;
    double epsilon = 1e-12;

    void step(ParticleStore& particles, ParticleStore& particles_test, double dt);
  };

  class WHFast {
  public:
    void step(ParticleStore& particles, ParticleStore& particles_test, double dt);
  };

  class IAS15 {
  public:
    void step(ParticleStore& particles, ParticleStore& particles_test, double dt);
  };

  class Mercurius {
  public:
    void step(ParticleStore& particles, ParticleStore& particles_test, double dt);
  };
} // namespace fnb

#endif
