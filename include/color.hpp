#pragma once

#include "./vec3.hpp"
#include <ostream>

int linear_to_gamma(int intensity);

class Color : public vec3 {
public:

  Color (double r, double g, double b) : vec3 (r, g, b){};

  Color(vec3 source) : vec3(source.get_x(), source.get_y(), source.get_z()) {}
  
  friend std::ostream& operator<<(std::ostream& os, Color &c) {
    os << (int) (255 * c.x) << ' ' << (int) (255 * c.y) << ' ' << (int) (255 * c.z);
    return os;
  }

  Color operator+(const Color &b) {
    return Color(x + b.get_x(), y + b.get_y(), z + b.get_z());
  }

  Color operator*(const double m) {
    return Color ( m * get_x(), m * get_y(), m * get_z());
  }

};

Color operator* (const Color& c1, const Color& c2);



