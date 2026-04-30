#include "freshnbody.hpp"
#include <set>

namespace fnb {
  namespace {
    template <typename T> void swap_last(SyncStore<T>& v, size_t idx) { std::swap(v.back(), v[idx]); }
  } // namespace

  void ParticleStore::add_particle(const IndParticle& p) {
    if (p.is_test) {
      positions.push_back(p.pos);
      velocities.push_back(p.vel);
      accelerations.push_back({0, 0, 0});
      mus.push_back(p.mu);
      ids.push_back(p.id);
      if (!test_thres_) {
        test_thres_ = N();
      }
    } else {
      if (test_thres_) {
        size_t& idx = test_thres_.value();
        positions.insert(idx - 1, p.pos);
        velocities.insert(idx - 1, p.vel);
        accelerations.insert(idx - 1, {0, 0, 0});
        mus.insert(idx - 1, p.mu);
        ids.insert(idx - 1, p.id);
        idx += 1;
      } else {
        positions.push_back(p.pos);
        velocities.push_back(p.vel);
        accelerations.push_back({0, 0, 0});
        mus.push_back(p.mu);
        ids.push_back(p.id);
      }
    }
  }

  void ParticleStore::add_particles(const std::vector<IndParticle>& ps) {
    for (const auto& p : ps) add_particle(p);
  }

  IndParticle ParticleStore::remove_particle(size_t idx) {
    IndParticle res;
    if (idx == N() - 1) {
      if (test_thres_) {
        auto& thres = test_thres_.value();
        if (thres == N() - 1) test_thres_ = {};
      }
      res.pos = positions.back();
      res.vel = velocities.back();
      res.id = ids.back();
      res.is_test = true;
      res.mu = mus.back();
      positions.pop_back();
      velocities.pop_back();
      accelerations.pop_back();
      mus.pop_back();
      ids.pop_back();
      return res;
    }

    if (test_thres_) {
      auto& thres = test_thres_.value();
      if (idx >= thres) {
        res.pos = positions[idx];
        res.vel = velocities[idx];
        res.id = ids[idx];
        res.is_test = true;
        res.mu = mus[idx];
        swap_last(positions, idx);
        swap_last(velocities, idx);
        swap_last(accelerations, idx);
        swap_last(mus, idx);
        swap_last(ids, idx);
        positions.pop_back();
        velocities.pop_back();
        accelerations.pop_back();
        mus.pop_back();
        ids.pop_back();
        --thres;
      } else {
        res.pos = positions[idx];
        res.vel = velocities[idx];
        res.id = ids[idx];
        res.mu = mus[idx];
        positions.erase(idx);
        velocities.erase(idx);
        accelerations.erase(idx);
        ids.erase(idx);
        mus.erase(idx);
        --thres;
      }
    } else {
      res.pos = positions[idx];
      res.vel = velocities[idx];
      res.id = ids[idx];
      res.mu = mus[idx];
      swap_last(positions, idx);
      swap_last(velocities, idx);
      swap_last(accelerations, idx);
      swap_last(mus, idx);
      swap_last(ids, idx);
      positions.pop_back();
      velocities.pop_back();
      accelerations.pop_back();
      mus.pop_back();
      ids.pop_back();
    }
    return res;
  }

  std::vector<IndParticle> ParticleStore::remove_particles(const std::vector<size_t>& idxs) {
    std::set s(idxs.begin(), idxs.end());
    std::vector<IndParticle> res;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      res.push_back(remove_particle(*it));
    }

    return res;
  }

  template <> SyncStore<double>& ParticleStore::get<double>(std::string_view param_name) {
    auto& extra_params = extra_params_dbl_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<double>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }

  template <> SyncStore<Vec3>& ParticleStore::get<Vec3>(std::string_view param_name) {
    auto& extra_params = extra_params_vec_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<Vec3>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }

  template <> SyncStore<uint64_t>& ParticleStore::get<uint64_t>(std::string_view param_name) {
    auto& extra_params = extra_params_int_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<uint64_t>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }

  template <> SyncStore<void*>& ParticleStore::get<void*>(std::string_view param_name) {
    auto& extra_params = extra_params_ptr_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<void*>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }

  template <> const SyncStore<double>& ParticleStore::get<double>(std::string_view param_name) const {
    auto& extra_params = extra_params_dbl_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<double>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }

  template <> const SyncStore<Vec3>& ParticleStore::get<Vec3>(std::string_view param_name) const {
    auto& extra_params = extra_params_vec_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<Vec3>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }

  template <> const SyncStore<uint64_t>& ParticleStore::get<uint64_t>(std::string_view param_name) const {
    auto& extra_params = extra_params_int_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<uint64_t>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }

  template <> const SyncStore<void*>& ParticleStore::get<void*>(std::string_view param_name) const {
    auto& extra_params = extra_params_ptr_;
    if (auto it = std::find_if(
            extra_params.begin(), extra_params.end(),
            [param_name](const std::pair<std::string_view, SyncStore<void*>>& el) { return el.first == param_name; });
        it != extra_params.end())
      return it->second;
    else
      throw std::invalid_argument("Parameter not found");
  }
} // namespace fnb
