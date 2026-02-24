#ifndef FRESHNBODY_HPP_
#define FRESHNBODY_HPP_

#include <cmath>

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
      double inv = 1 / other;
      operator*=(inv);
      return *this;
    }

    inline constexpr double dot(Vec3 other) const { return x * other.x + y * other.y + z * other.z; }
    inline constexpr double mag2() const { return dot(*this); }
    inline double mag() const { return std::sqrt(mag2()); }
    inline constexpr double dist2(Vec3 other) const { return (other - *this).mag2(); }
    inline double dist(Vec3 other) const { return std::sqrt(dist2(other)); }
    inline constexpr bool almost_eq(Vec3 other, double thres = 1e-9) const { return dist2(other) < thres; }

  private:
    template <typename T> inline constexpr T ce_abs(T a) { return a < 0 ? -a : a; }
  };

  inline constexpr Vec3 operator+(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
  inline constexpr Vec3 operator-(Vec3 a, Vec3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
  inline constexpr Vec3 operator*(Vec3 a, double b) { return {a.x * b, a.y * b, a.z * b}; }
  inline constexpr Vec3 operator/(Vec3 a, double b) {
    double inv = 1 / b;
    return a * inv;
  }

  inline constexpr Vec3 operator*(double a, Vec3 b) { return b * a; }
  inline constexpr bool operator==(Vec3 a, Vec3 b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
  inline constexpr bool operator!=(Vec3 a, Vec3 b) { return !(a == b); }
} // namespace fnb

#endif