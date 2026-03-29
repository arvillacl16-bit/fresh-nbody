#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#include "integrator.hpp"
#include "particle.hpp"
#include "vec.hpp"
#include <cstdint>
#include <functional>

namespace fnb {
  enum class Integrator : uint8_t { NONE = 0, LEAPFROG, WHFAST, IAS15, MERCURIUS };

  class Simulation {
  private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;

    double t_;

    ParticleStore particles_;
    ParticleStore particles_test_;

  public:
    enum class Status : uint8_t { OK = 0, TERM };

    double dt;

    union {
      Integrator integrator;
      Leapfrog leapfrog;
      WHFast whfast;
      IAS15 ias15;
      Mercurius mercurius;
    } config;

    std::function<Status(Simulation&)> heartbeat;

    Simulation() = delete;
    Simulation(const Simulation&);
    Simulation(Simulation&&) noexcept;
    Simulation& operator=(const Simulation&);
    Simulation& operator=(Simulation&&) noexcept;
    ~Simulation();
  };
} // namespace fnb

#endif
