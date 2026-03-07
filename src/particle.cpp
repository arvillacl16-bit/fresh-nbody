#include "freshnbody.hpp"
#include <set>

namespace fnb {
  namespace {
    template <typename T> void swap_last(std::vector<T>& v, size_t idx) { std::swap(v.back(), v[idx]); }
  } // namespace

  void ParticleStore::add_particle(const IndParticle& p) {
    positions.push_back(p.pos);
    velocities.push_back(p.vel);
    accelerations.push_back(p.acc);
    masses.push_back(p.mass);
    ids.push_back(p.id);

    ++N;
  }

  void ParticleStore::add_particles(const std::vector<IndParticle>& ps) {
    for (const auto& p : ps) {
      positions.push_back(p.pos);
      velocities.push_back(p.vel);
      accelerations.push_back(p.acc);
      masses.push_back(p.mass);
      ids.push_back(p.id);
    }

    N += ps.size();
  }

  IndParticle ParticleStore::remove_particle(size_t idx) {
    --N;

    swap_last(positions, idx);
    swap_last(velocities, idx);
    swap_last(accelerations, idx);
    swap_last(masses, idx);
    swap_last(ids, idx);

    IndParticle res;
    res.pos = positions.back();
    res.vel = velocities.back();
    res.acc = accelerations.back();
    res.mass = masses.back();
    res.id = ids.back();

    positions.pop_back();
    velocities.pop_back();
    accelerations.pop_back();
    masses.pop_back();
    ids.pop_back();
    return res;
  }

  std::vector<IndParticle> ParticleStore::remove_particles(const std::vector<size_t>& idxs) {
    std::set s(idxs.begin(), idxs.end());
    std::vector<IndParticle> res;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      size_t idx = *it;
      swap_last(positions, idx);
      swap_last(velocities, idx);
      swap_last(accelerations, idx);
      swap_last(masses, idx);
      swap_last(ids, idx);

      IndParticle p;
      p.pos = positions.back();
      p.vel = velocities.back();
      p.acc = accelerations.back();
      p.mass = masses.back();
      p.id = ids.back();

      positions.pop_back();
      velocities.pop_back();
      accelerations.pop_back();
      masses.pop_back();
      ids.pop_back();

      res.push_back(p);
    }

    N -= s.size();
    return res;
  }
} // namespace fnb