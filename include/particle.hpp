#ifndef FRESHNBODY_HPP_
#define FRESHNBODY_HPP_

#include "vec.hpp"
#include <vector>

namespace fnb {
  struct IndParticle {
    Vec3 pos;
    Vec3 vel;
    Vec3 acc;
    double mu;
    uint64_t id;
  };

  class Particle;
  class ConstParticle;

  class ParticleStore {
  private:
    size_t N = 0;

    std::vector<Vec3> positions;
    std::vector<Vec3> velocities;
    std::vector<Vec3> accelerations;
    std::vector<double> mus;
    std::vector<uint64_t> ids;

  public:
    ParticleStore() = default;
    ParticleStore(size_t N_) : N(N_) {}

    void add_particle(const IndParticle& p);
    void add_particles(const std::vector<IndParticle>& ps);
    IndParticle remove_particle(size_t idx);
    std::vector<IndParticle> remove_particles(const std::vector<size_t>& idxs);

    Particle operator[](size_t idx);
    ConstParticle operator[](size_t idx) const;

    friend class Particle;
    friend class ConstParticle;
  };

  class Particle {
  private:
    ParticleStore* ps_ = nullptr;
    size_t idx_ = 0;

  public:
    Particle(ParticleStore& ps, size_t idx) : ps_(&ps), idx_(idx) {}

    Vec3& pos() { return ps_->positions[idx_]; }
    Vec3& vel() { return ps_->velocities[idx_]; }
    Vec3& acc() { return ps_->accelerations[idx_]; }
    double& mass() { return ps_->mus[idx_]; }
    uint64_t& id() { return ps_->ids[idx_]; }

    operator ConstParticle();
  };

  class ConstParticle {
  private:
    const ParticleStore* ps_ = nullptr;
    size_t idx_ = 0;

  public:
    ConstParticle(const ParticleStore& ps, size_t idx) : ps_(&ps), idx_(idx) {}

    Vec3 pos() const { return ps_->positions[idx_]; }
    Vec3 vel() const { return ps_->velocities[idx_]; }
    Vec3 acc() const { return ps_->accelerations[idx_]; }
    double mu() const { return ps_->mus[idx_]; }
    uint64_t id() const { return ps_->ids[idx_]; }
  };

  inline Particle ParticleStore::operator[](size_t idx) { return Particle(*this, idx); }
  inline ConstParticle ParticleStore::operator[](size_t idx) const { return ConstParticle(*this, idx); }

  inline Particle::operator ConstParticle() { return ConstParticle(*ps_, idx_); }
} // namespace fnb

#endif