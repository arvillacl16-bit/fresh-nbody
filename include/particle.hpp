#ifndef FRESHNBODY_HPP_
#define FRESHNBODY_HPP_

#include "vec.hpp"
#include <cstdint>
#include <stdexcept>
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

  template <typename T> class SyncStore {
  private:
    std::vector<T> data_;
    T def_val_{};

    SyncStore() = default;

    SyncStore(const std::vector<T>& data) : data_(data) {}
    SyncStore(const std::vector<T>& data, const T& def_val) : data_(data), def_val_(def_val) {}
    SyncStore(size_t N) : data_(N) {}
    SyncStore(size_t N, const T& def_val) : data_(N), def_val_(def_val) {}

    template <typename... Args> SyncStore(Args&&... args) : def_val_(std::forward<Args>(args)...) {}

    void push_back(const T& el) { data_.push_back(el); }
    void pop_back() { return data_.pop_back(); }
    void push_back(T&& el) { data_.push_back(el); }

    template <typename... Args> void emplace_back(Args&&... args) { data_.emplace_back(std::forward<Args>(args)...); }

    void resize(size_t sz) { data_.resize(sz); }
    void reserve(size_t sz) { data_.reserve(sz); }

  public:
    operator const std::vector<T>&() const { return data_; }

    T& operator[](size_t idx) { return data_[idx]; }
    const T& operator[](size_t idx) const { return data_[idx]; }

    T& at(size_t idx) { return data_.at(idx); }
    const T& at(size_t idx) const { return data_.at(idx); }

    size_t size() const { return data_.size(); }
    size_t capacity() const { return data_.capacity(); }

    T& back() { return data_.back(); }

    auto begin() { return data_.begin(); }
    auto begin() const { return data_.begin(); }
    auto end() { return data_.end(); }
    auto end() const { return data_.end(); }

    auto cbegin() const { return data_.cbegin(); }
    auto cend() const { return data_.cend(); }

    friend class ParticleStore;
  };

  template <typename T>
  using VecMap = std::vector<std::pair<std::string_view, SyncStore<T>>>;

  class ParticleStore {
  private:
    VecMap<double> extra_params_dbl_;
    VecMap<Vec3> extra_params_vec_;
    VecMap<uint64_t> extra_params_int_;
    VecMap<void*> extra_params_ptr_;

  public:
    SyncStore<Vec3> positions;
    SyncStore<Vec3> velocities;
    SyncStore<Vec3> accelerations;
    SyncStore<double> mus;
    SyncStore<uint64_t> ids;

    template <typename T> SyncStore<T>& get(std::string_view) { static_assert(false, "Invalid type"); }
    template <typename T> const SyncStore<T>& get(std::string_view) const { static_assert(false, "Invalid type"); }

    template<> SyncStore<double>& get<double>(std::string_view param_name) {
      auto& extra_params = extra_params_dbl_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<double>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }

    template<> SyncStore<Vec3>& get<Vec3>(std::string_view param_name) {
      auto& extra_params = extra_params_vec_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<Vec3>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }

    template<> SyncStore<uint64_t>& get<uint64_t>(std::string_view param_name) {
      auto& extra_params = extra_params_int_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<uint64_t>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }

    template<> SyncStore<void*>& get<void*>(std::string_view param_name) {
      auto& extra_params = extra_params_ptr_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<void*>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }
    template<> const SyncStore<double>& get<double>(std::string_view param_name) const {
      auto& extra_params = extra_params_dbl_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<double>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }

    template<> const SyncStore<Vec3>& get<Vec3>(std::string_view param_name) const {
      auto& extra_params = extra_params_vec_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<Vec3>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }

    template<> const SyncStore<uint64_t>& get<uint64_t>(std::string_view param_name) const {
      auto& extra_params = extra_params_int_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<uint64_t>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }

    template<> const SyncStore<void*>& get<void*>(std::string_view param_name) const {
      auto& extra_params = extra_params_ptr_;
      if (auto it = std::find_if(extra_params.begin(), extra_params.end(), 
          [param_name](const std::pair<std::string_view, SyncStore<void*>>& el) { return el.first == param_name; }); 
          it != extra_params.end()) return it->second;
      else throw std::invalid_argument("Parameter not found");
    }


    ParticleStore() = default;
    ParticleStore(size_t N) : positions(N), velocities(N), accelerations(N), mus(N), ids(N) {}

    ParticleStore(const ParticleStore&) = default;
    ParticleStore(ParticleStore&&) = default;
    ParticleStore& operator=(const ParticleStore&) = default;
    ParticleStore& operator=(ParticleStore&&) = default;

    void add_particle(const IndParticle& p);
    void add_particles(const std::vector<IndParticle>& ps);
    IndParticle remove_particle(size_t idx);
    std::vector<IndParticle> remove_particles(const std::vector<size_t>& idxs);

    Particle operator[](size_t idx);
    ConstParticle operator[](size_t idx) const;

    size_t N() { return positions.size(); } 

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
    double& mu() { return ps_->mus[idx_]; }
    uint64_t& id() { return ps_->ids[idx_]; }
    Vec3 pos() const { return ps_->positions[idx_]; }
    Vec3 vel() const { return ps_->velocities[idx_]; }
    Vec3 acc() const { return ps_->accelerations[idx_]; }
    double mu() const { return ps_->mus[idx_]; }
    uint64_t id() const { return ps_->ids[idx_]; }

    operator ConstParticle() const;
    operator IndParticle() const {
      IndParticle res;
      res.pos = pos();
      res.vel = vel();
      res.acc = acc();
      res.mu = mu();
      res.id = id();
      return res;
    }
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
    operator IndParticle() const {
      IndParticle res;
      res.pos = pos();
      res.vel = vel();
      res.acc = acc();
      res.mu = mu();
      res.id = id();
      return res;
    }
  };

  inline Particle ParticleStore::operator[](size_t idx) { return Particle(*this, idx); }
  inline ConstParticle ParticleStore::operator[](size_t idx) const { return ConstParticle(*this, idx); }

  inline Particle::operator ConstParticle() const { return ConstParticle(*ps_, idx_); }
} // namespace fnb

#endif
