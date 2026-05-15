#include "particle.hpp"
#include "freshnbody.hpp"
#include <stdexcept>

namespace fnb {
  namespace {
    template <typename T> void swap_last(SyncStore<T>& v, size_t idx) { std::swap(v.back(), v[idx]); }
  } // namespace

  void ParticleStore::add_particle(const IndParticle& p) {
    positions.push_back(p.pos);
    velocities.push_back(p.vel);
    accelerations.push_back({});
    mus.push_back(p.mu);
    ids.push_back(p.id);

    if (p.is_test && !test_thres_) test_thres_ = N() - 1; 
    else if (test_thres_) {
      size_t target_idx = test_thres_.value();
      size_t last_idx = N() - 1;

      std::swap(positions[target_idx], positions[last_idx]);
      std::swap(velocities[target_idx], velocities[last_idx]);
      std::swap(accelerations[target_idx], accelerations[last_idx]);
      std::swap(mus[target_idx], mus[last_idx]);
      std::swap(ids[target_idx], ids[last_idx]);

      test_thres_.value() += 1;
    }
  }

  void ParticleStore::add_particles(const std::vector<IndParticle>& ps) {
    for (const auto& p : ps) add_particle(p);
  }

  IndParticle ParticleStore::remove_particle(size_t idx) {
    if (idx >= N()) throw std::out_of_range("Index out of bounds");

    IndParticle res;
    res.pos = positions[idx];
    res.vel = velocities[idx];
    res.mu = mus[idx];
    res.id = ids[idx];
    res.is_test = (test_thres_ && idx >= test_thres_.value());

    size_t last_idx = N() - 1;

    if (res.is_test) {
      swap_last(positions, idx);
      swap_last(velocities, idx);
      swap_last(accelerations, idx);
      swap_last(mus, idx);
      swap_last(ids, idx);

      if (test_thres_ && test_thres_.value() == last_idx) test_thres_ = std::nullopt; 
    } else {
      if (test_thres_) {
        size_t last_massive_idx = test_thres_.value() - 1;

        std::swap(positions[idx], positions[last_massive_idx]);
        std::swap(velocities[idx], velocities[last_massive_idx]);
        std::swap(accelerations[idx], accelerations[last_massive_idx]);
        std::swap(mus[idx], mus[last_massive_idx]);
        std::swap(ids[idx], ids[last_massive_idx]);

        swap_last(positions, last_massive_idx);
        swap_last(velocities, last_massive_idx);
        swap_last(accelerations, last_massive_idx);
        swap_last(mus, last_massive_idx);
        swap_last(ids, last_massive_idx);

        test_thres_.value() -= 1;
      } else {
        swap_last(positions, idx);
        swap_last(velocities, idx);
        swap_last(accelerations, idx);
        swap_last(mus, idx);
        swap_last(ids, idx);
      }
    }

    positions.pop_back();
    velocities.pop_back();
    accelerations.pop_back();
    mus.pop_back();
    ids.pop_back();

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
