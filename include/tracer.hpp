#pragma once
#include "./vec3.hpp"
#include "./ray.hpp"
#include "./env.hpp"
#include "./utils.hpp"
#include <cstddef>
#include <vector>

// A TraceRecord wraps every data needed for the tracer to take proper action after a hit
class TraceRecord {
  public:
  vec3 n;
  bool hit;

  TraceRecord() = default;
  TraceRecord(bool hit, vec3 n) : n(n), hit(hit){}

  static TraceRecord nohit() {
    TraceRecord r;
    r.hit = false;
    return r;
  }

};


class RayTracer {
  // Fov
  double fov;

  // Size of the viewport (in real world size)
  double width, height;

  // Size of the viewport (in px)
  size_t px_w, px_h;

  // Pixels
  std::vector<Color> pixels;

  // Viewports utils
  double dx, dz;
  vec3 xv, zv, yv;
  double focal_length;

  // Defocus
  double defocus_angle;
  double focus_distance;
  double defocus_radius;
  
  // Rays
  std::vector<Ray> rays;
  
  // Position
  vec3 from, to, vertical;

  // Anti aliasing config
  bool antialiasing = true;
  int super_sampling_rate = 10;
  

  public:
  // Environment
  std::unique_ptr<Environment> env;

  // Getters
  std::vector<Ray>& get_rays();
  
  // Antialiasing
  Color super_sample(size_t x, size_t y, int rate);

  // Rays
  void init_rays();
  TraceRecord trace(Ray&, interval<double> i);
  Ray get_ray(size_t x, size_t y, const bool randomize);
  
  RayTracer (double fov,size_t px_w, size_t px_h, vec3 from, vec3 to, vec3 vertical, double defocus_distance, double defocus_angle) : fov(fov), px_w(px_w), px_h(px_h), from(from), to(to), vertical(vertical), defocus_angle(defocus_angle), focus_distance(defocus_distance){}
  void render();
  void set_env(std::unique_ptr<Environment>);
  void dump_image();

};