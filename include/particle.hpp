#ifndef FRESHNBODY_HPP_
#define FRESHNBODY_HPP_

#include "vec.hpp"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>
#include <vector>

namespace fnb {
  struct IndParticle {
    Vec3 pos;
    Vec3 vel;
    double mu;
    uint64_t id;
    bool is_test = false;
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
    void pop_back() { data_.pop_back(); }
    void push_back(T&& el) { data_.push_back(el); }

    void insert(size_t i, const T& val) { data_.insert(data_.begin() + i, val); }
    void insert(size_t i, T&& val) { data_.insert(data_.begin() + i, val); }

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

  template <typename T> using VecMap = std::vector<std::pair<std::string_view, SyncStore<T>>>;

  class ParticleStore {
  private:
    VecMap<double> extra_params_dbl_;
    VecMap<Vec3> extra_params_vec_;
    VecMap<uint64_t> extra_params_int_;
    VecMap<void*> extra_params_ptr_;

    std::optional<size_t> test_thres_;

  public:
    SyncStore<Vec3> positions;
    SyncStore<Vec3> velocities;
    SyncStore<Vec3> accelerations;
    SyncStore<double> mus;
    SyncStore<uint64_t> ids;

    template <typename T> SyncStore<T>& get(std::string_view) { static_assert(sizeof(T) == 0, "Invalid type"); }
    template <typename T> const SyncStore<T>& get(std::string_view) const { static_assert(sizeof(T) == 0, "Invalid type"); }

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
    auto test_thres() { return test_thres_; }

    friend class Particle;
    friend class ConstParticle;
  };

  template <> SyncStore<double>& ParticleStore::get(std::string_view);
  template <> SyncStore<Vec3>& ParticleStore::get(std::string_view);
  template <> SyncStore<void*>& ParticleStore::get(std::string_view);
  template <> SyncStore<uint64_t>& ParticleStore::get(std::string_view);
  template <> const SyncStore<double>& ParticleStore::get(std::string_view) const;
  template <> const SyncStore<Vec3>& ParticleStore::get(std::string_view) const;
  template <> const SyncStore<void*>& ParticleStore::get(std::string_view) const;
  template <> const SyncStore<uint64_t>& ParticleStore::get(std::string_view) const;

  class Particle {
  private:
    ParticleStore* ps_ = nullptr;
    size_t idx_ = 0;

  public:
    Particle(ParticleStore& ps, size_t idx) : ps_(&ps), idx_(idx) {}

    Vec3& pos() { return ps_->positions[idx_]; }
    Vec3& vel() { return ps_->velocities[idx_]; }
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
