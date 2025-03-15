#pragma once
#include "./vec3.hpp"
#include "./color.hpp"

class Ray {
  private:
  vec3 origin;
  vec3 direction;
  Color color;

  public: 
  Ray(double x, double y, double z, double dx, double dy, double dz) : origin(x, y, z), direction(dx, dy, dz), color(0,0,0){};
  Ray(vec3 origin, vec3 direction) : origin(origin), direction(direction), color(0,0,0){}

  vec3 get_origin() {
    return origin;
  };

  vec3 get_direction() {
    return direction;
  };

  void set_color(Color c) {
    color = c;
  }

  Color& get_color() {
    return color;
  }

  friend std::ostream& operator<<(std::ostream& os, const Ray& r) {
    os << "o : " << r.origin << " - d : " << r.direction << std::endl; 
    return os;
  }
};

