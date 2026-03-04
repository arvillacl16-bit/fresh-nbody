#ifndef FRESHNBODY_HPP_
#define FRESHNBODY_HPP_

#include <cmath>
#include <vector>

namespace fnb {
  struct Vec3;
  inline constexpr Vec3 operator-(Vec3 a, Vec3 b);

  struct Vec3 {
    double x = 0, y = 0, z = 0;

    constexpr Vec3() = default;
    constexpr explicit Vec3(double x_) : x(x_) {}
    constexpr Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    inline Vec3& operator+=(Vec3 other) {
      x += other.x;
      y += other.y;
      z += other.z;
      return *this;
    }

    inline Vec3& operator-=(Vec3 other) {
      x -= other.x;
      y -= other.y;
      z -= other.z;
      return *this;
    }

    inline Vec3& operator*=(double other) {
      x *= other;
      y *= other;
      z *= other;
      return *this;
    }

    inline Vec3& operator/=(double other) {
      double inv = 1. / other;
      operator*=(inv);
      return *this;
    }

    [[nodiscard]] inline constexpr double dot(Vec3 other) const { return x * other.x + y * other.y + z * other.z; }
    [[nodiscard]] inline constexpr double mag2() const { return dot(*this); }
    [[nodiscard]] inline double mag() const { return std::sqrt(mag2()); }
    [[nodiscard]] inline constexpr double dist2(Vec3 other) const { return (other - *this).mag2(); }
    [[nodiscard]] inline double dist(Vec3 other) const { return std::sqrt(dist2(other)); }
    [[nodiscard]] inline constexpr bool almost_eq(Vec3 other, double thres = 1e-9) const { return dist2(other) < thres * thres; }

  private:
    template <typename T> inline constexpr T ce_abs(T a) { return a < 0 ? -a : a; }
  };

  [[nodiscard]] inline constexpr Vec3 operator+(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
  [[nodiscard]] inline constexpr Vec3 operator-(Vec3 a, Vec3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
  [[nodiscard]] inline constexpr Vec3 operator*(Vec3 a, double b) { return {a.x * b, a.y * b, a.z * b}; }
  [[nodiscard]] inline constexpr Vec3 operator/(Vec3 a, double b) {
    double inv = 1. / b;
    return a * inv;
  }

  [[nodiscard]] inline constexpr Vec3 operator*(double a, Vec3 b) { return b * a; }
  [[nodiscard]] inline constexpr bool operator==(Vec3 a, Vec3 b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
  [[nodiscard]] inline constexpr bool operator!=(Vec3 a, Vec3 b) { return !(a == b); }
  [[nodiscard]] inline constexpr Vec3 operator+(Vec3 a) { return a; }
  [[nodiscard]] inline constexpr Vec3 operator-(Vec3 a) { return {-a.x, -a.y, -a.z}; }

  struct IndParticle {
    Vec3 pos;
    Vec3 vel;
    Vec3 acc;
    double mass;
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
    std::vector<double> masses;
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
    double& mass() { return ps->masses[idx]; }
    uint64_t& id() { return ps->ids[idx]; }

    operator ConstParticle();
  };

  class ConstParticle {
  private:
    const ParticleStore* ps = nullptr;
    size_t idx = 0;

  public:
    ConstParticle(const ParticleStore& ps_, size_t idx_) : ps(&ps_), idx(idx_) {}

    Vec3 pos() { return ps->positions[idx]; }
    Vec3 vel() { return ps->velocities[idx]; }
    Vec3 acc() { return ps->accelerations[idx]; }
    double mass() { return ps->masses[idx]; }
    uint64_t id() { return ps->ids[idx]; }
  };

  inline Particle ParticleStore::operator[](size_t idx) { return Particle(*this, idx); }
  inline ConstParticle ParticleStore::operator[](size_t idx) const { return ConstParticle(*this, idx); }

  inline Particle::operator ConstParticle() { return ConstParticle(*ps, idx); }
} // namespace fnb

#endif