#ifndef INTEGRATOR_HPP_
#define INTEGRATOR_HPP_

#include "particle.hpp"

namespace fnb {
  class Leapfrog {
  public:
    void step(ParticleStore& particles, double dt);
  };

  class WHFast {
  public:
    void step(ParticleStore& particles, double dt);
  };

  class IAS15 {
  public:
    void step(ParticleStore& particles, double dt);
  };

  class Mercurius {
  public:
    void step(ParticleStore& particles, double dt);
  };
} // namespace fnb

#endif