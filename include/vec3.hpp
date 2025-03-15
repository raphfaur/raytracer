#pragma once
#include <cmath>
#include <iostream>
#include <ostream>

class vec3 {
protected:
  double x;
  double y;
  double z;

public:
  vec3(double x, double y, double z) : x(x), y(y), z(z) {}
  vec3() = default;

  // Getters

  double get_x() const { return x; }

  double get_y() const { return y; }

  double get_z() const { return z; }

  // Maths utils

  // Normalize to unitary norm
  void normalize() {
    normalize_by(std::sqrt(norm_square()));
  }

  // Normalize to given norm
  void normalize_by(double norm) {
    x /= norm;
    y /= norm;
    z /= norm;
  }

  // Get norm
  double norm_square() {
    return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
  }

  double norm() {
    return std::sqrt(norm_square());
  }

  vec3 operator+(const vec3 &b) {
    return vec3(x + b.get_x(), y + b.get_y(), z + b.get_z());
  }

  friend std::ostream &operator<<(std::ostream &os, const vec3 &v) {
    os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return os;
  }

  static vec3 random(double min, double max);
  static vec3 random_unit();
  static vec3 random_flat_unit();
};

vec3 operator*(const int m, const vec3 &v);
vec3 operator*(const double m, const vec3 &v);

vec3 operator-(const vec3 &a, const vec3 &b);

double dot(vec3 &a, vec3 &b);
vec3 cross_product(vec3 &a, vec3 &b);