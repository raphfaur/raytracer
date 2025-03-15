#include "./include/vec3.hpp"
#include "./include/utils.hpp"

vec3 operator*(const int m, const vec3 &v) {
  return vec3(m * v.get_x(), m * v.get_y(), m * v.get_z());
}
vec3 operator*(const double m, const vec3 &v) {
  return vec3(m * v.get_x(), m * v.get_y(), m * v.get_z());
}
double dot(vec3 &a, vec3 &b) {
  return (a.get_x() * b.get_x() + a.get_y() * b.get_y() +
          a.get_z() * b.get_z());
}

vec3 cross_product(vec3 &a, vec3 &b) {
  return vec3(a.get_y() * b.get_z() - a.get_z() * b.get_y(),
              a.get_z() * b.get_x() - a.get_x() * b.get_z(),
              a.get_x() * b.get_y() - a.get_y() * b.get_x());
}

vec3 operator-(const vec3 &a, const vec3 &b) {
  return vec3(a.get_x() - b.get_x(), a.get_y() - b.get_y(),
              a.get_z() - b.get_z());
}

vec3 vec3::random(double min, double max) {
  return vec3(random_double(min, max), random_double(min, max),
              random_double(min, max));
}

vec3 vec3::random_unit() {
  while (true) {
    auto v = vec3::random(-1, 1);
    if (1e-160 < v.norm_square()) {
      v.normalize();
      return v;
    }
  }
}

vec3 vec3::random_flat_unit() {
    while (true) {
      auto v = vec3(random_double(-1, 1), random_double(-1, 1), 0);
      if (1e-160 < v.norm_square()) {
        v.normalize();
        return v;
      }
    }
  }
