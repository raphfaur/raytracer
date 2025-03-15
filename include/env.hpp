#pragma once
#include "./ray.hpp"
#include <memory>

class Texture;

class Shape {
public:
  virtual double intersect(Ray &r, vec3 position) = 0;
  virtual ~Shape(){};
  std::shared_ptr<Texture> texture;
  void set_texture(std::shared_ptr<Texture> t);
};

class Sphere : public Shape {
  double r;

public:
  Sphere(double r) : r(r) {}
  virtual double intersect(Ray &r, vec3 position) override;
  virtual ~Sphere() = default;
};

class Environment {
private:
  std::vector<std::pair<std::unique_ptr<Shape>, vec3>> shapes;

public:
  Environment() = default;
  void at(vec3 position, Shape *);
  std::vector<std::pair<std::unique_ptr<Shape>, vec3>> &get_shapes();
};

class Texture {
public:
  // Return the scattered ray given the hitpoint and the normal
  virtual Ray reflected_ray(vec3 &hitpoint, vec3 &normal, Ray& source) = 0;

  // The attenuation color
  virtual Color attenuation(vec3 &hitpoint, vec3 &normal) = 0;

  virtual ~Texture(){};
};

class BasicTexture : public Texture {
  Color albedo;

public:
  BasicTexture(Color c) : albedo(c) {}
  virtual ~BasicTexture() = default;
  virtual Color attenuation(vec3 &hitpoint, vec3 &normal) override;
  virtual Ray reflected_ray(vec3 &hitpoint, vec3 &normal, Ray& source) override;
};

class Metal : public Texture {
  Color albedo;
  double fuzz;

public:
  Metal(Color c, double fuzz) : albedo(c), fuzz(fuzz) {}
  virtual ~Metal() = default;
  virtual Color attenuation(vec3 &hitpoint, vec3 &normal) override;
  virtual Ray reflected_ray(vec3 &hitpoint, vec3 &normal, Ray& source) override;
};