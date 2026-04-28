#include "simulation.hpp"
#include "particle.hpp"
#include <memory>
#include <unordered_map>
#include <iostream>

namespace fnb {
  struct Simulation::Impl {
    std::unordered_map<uint64_t, size_t> id_map;
  };

  Simulation::Simulation(Simulation&&) noexcept = default;
  Simulation& Simulation::operator=(Simulation&&) noexcept = default;

  Simulation::Simulation(const Simulation& other)
      : pimpl_(std::make_unique<Impl>()), t_(other.t_), particles_(other.particles_), particles_test_(other.particles_test_),
        config(other.config), dt(other.dt) {
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

  using Status = Simulation::Status;
  static std::string_view status_to_str(Status status) {
    switch (status) {
    case Status::TERM:
      return "TERM";
    default:
      return "";
    }
  }

  void Simulation::step(double dt) {
    switch (config.type()) {
    case IntegratorType::LEAPFROG:
      config.get<Leapfrog>().step(particles_, dt);
      break;
    case IntegratorType::WHFAST:
      config.get<WHFast>().step(particles_, dt);
      break;
    case IntegratorType::IAS15:
      config.get<IAS15>().step(particles_, dt);
      break;
    case IntegratorType::MERCURIUS:
      config.get<Mercurius>().step(particles_, dt);
      break;
    default:
      int _;
    }
  }

  void Simulation::integrate(double t, bool exact) {
    while (t_ < t) {
      double step_size = exact ? (dt < t - t_ ? dt : t - t_) : dt;
      step(step_size);
      t_ += step_size;

      Status status = heartbeat(*this);
      if (status != Status::OK) std::cerr << "ERROR: Integration terminated with status " << status_to_str(status) << '\n';
    }
  }
} // namespace fnb
