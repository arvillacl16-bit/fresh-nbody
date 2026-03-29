#include "simulation.hpp"
#include "particle.hpp"
#include <memory>
#include <unordered_map>

namespace fnb {
  struct Simulation::Impl {
    std::unordered_map<uint64_t, size_t> id_map;
  };

  Simulation::Simulation(Simulation&&) noexcept = default;
  Simulation& Simulation::operator=(Simulation&&) noexcept = default;

  Simulation::Simulation(const Simulation& other)
    : pimpl_(std::make_unique<Impl>()), t_(other.t_), particles_(other.particles_), particles_test_(other.particles_test_),
      dt(other.dt), config(other.config) {
    pimpl_->id_map = other.pimpl_->id_map;
  }

  Simulation& Simulation::operator=(const Simulation& other) {
    if (this == &other) return *this;

    pimpl_ = std::make_unique<Impl>();
    t_ = other.t_;
    particles_ = other.particles_;
    particles_test_ = other.particles_test_;
    dt = other.dt;
    config = other.config;

    pimpl_->id_map = other.pimpl_->id_map;
    return *this;
  }
}
