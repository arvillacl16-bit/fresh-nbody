#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#include "integrator.hpp"
#include "particle.hpp"
#include "vec.hpp"

namespace fnb {
  enum class Integrator : uint8_t { NONE = 0, LEAPFROG, WHFAST, IAS15, MERCURIUS };

  class Simulation {
  private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;

    double t_;

    ParticleStore particles_;

  public:
    double dt;

    Integrator integrator;
    Leapfrog leapfrog;
    WHFast whfast;
    IAS15 ias15;
    Mercurius mercurius;

    Simulation();
  };
} // namespace fnb

#endif