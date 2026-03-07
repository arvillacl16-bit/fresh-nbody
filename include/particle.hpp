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
    ParticleStore* ps = nullptr;
    size_t idx = 0;

  public:
    Particle(ParticleStore& ps_, size_t idx_) : ps(&ps_), idx(idx_) {}

    Vec3& pos() { return ps->positions[idx]; }
    Vec3& vel() { return ps->velocities[idx]; }
    Vec3& acc() { return ps->accelerations[idx]; }
    double& mass() { return ps->mus[idx]; }
    uint64_t& id() { return ps->ids[idx]; }

    operator ConstParticle();
  };

  class ConstParticle {
  private:
    const ParticleStore* ps = nullptr;
    size_t idx = 0;

  public:
    ConstParticle(const ParticleStore& ps_, size_t idx_) : ps(&ps_), idx(idx_) {}

    Vec3 pos() const { return ps->positions[idx]; }
    Vec3 vel() const { return ps->velocities[idx]; }
    Vec3 acc() const { return ps->accelerations[idx]; }
    double mu() const { return ps->mus[idx]; }
    uint64_t id() const { return ps->ids[idx]; }
  };

  inline Particle ParticleStore::operator[](size_t idx) { return Particle(*this, idx); }
  inline ConstParticle ParticleStore::operator[](size_t idx) const { return ConstParticle(*this, idx); }

  inline Particle::operator ConstParticle() { return ConstParticle(*ps, idx); }
} // namespace fnb

#endif