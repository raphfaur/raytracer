#include "./include/tracer.hpp"
#include "./include/utils.hpp"
#include "./include/vec3.hpp"

#include <vector>

Ray RayTracer::get_ray(size_t x, size_t y, const bool randomize) {
  auto d = (to - from );
  d.normalize();
  auto direction = focus_distance * yv + ((-width / 2) + dx / 2 + x * dx) * xv + (height / 2 - dz / 2 - y * dz) * zv;

  if (randomize) {
    auto ddx = random_double(-1.0, +1.0) * dx / 2;
    auto ddz = random_double(-1.0, +1.0) * dz / 2;
    direction = direction + ddx * xv  + ddz * zv; 
  }

  // Compute origin in the defocus disk
  auto unit = vec3::random_flat_unit();
  auto origin = from + defocus_radius * (unit.get_x() * zv + unit.get_y() * xv);

  direction.normalize();
  auto ray = Ray(origin, direction);
  return ray;
}

// Compute all rays
void RayTracer::init_rays() {

  // Defocus setup
  auto beta = degre_to_radian(defocus_angle);
  defocus_radius = focus_distance * std::tan(beta / 2);

  // Viewport dimension
  double angle = degre_to_radian(fov);
  std::cerr << angle << std::endl;

  height = 2 * std::tan(angle/2) * focus_distance;
  width = px_w / px_h * height;

  std::cerr << height << std::endl;
  std::cerr << width << std::endl;

  
  // Compute dx and dy
  dx = width / px_w;
  dz = height / px_h;

  yv = to - from;
  xv = cross_product(yv, vertical);
  zv = cross_product(xv, yv);

  yv.normalize();
  xv.normalize();
  zv.normalize();
  std::cerr << xv << std::endl;
  std::cerr << yv << std::endl;
  std::cerr << zv << std::endl;
  xv = dx * xv;
  zv = dz * zv;
}

void RayTracer::set_env(std::unique_ptr<Environment> e) { env = std::move(e); }

Color RayTracer::super_sample(size_t x, size_t y, int samples) {
  Color acc(0, 0, 0);
  for (int i = 0; i < samples; i++) {
    auto ray = get_ray(x, y, true);
    // std::cerr << ray;
    trace(ray, interval<double>(0, interval<double>::infinity));
    auto c = ray.get_color();
    acc = acc + c;
  }
  return acc * ((double)1 / samples);
}

TraceRecord RayTracer::trace(Ray &ray, interval<double> i) {

  for (auto &s : env->get_shapes()) {

    auto t = s.first->intersect(ray, s.second);
    if (i.contains(t)) {
      auto hit_point = ray.get_origin() + t * ray.get_direction();
      auto n = hit_point - s.second;
      n.normalize();

      // Reflection
      // auto reflect_direction = n + vec3::random_unit();
      // auto reflected_ray = Ray(hit_point, reflect_direction);
      // auto newc = trace(reflected_ray, interval<double>(0.1,
      // interval<double>::infinity ));
      auto t = s.first->texture;
      auto reflected_ray = t->reflected_ray(hit_point, n, ray);
      auto albedo = t->attenuation(hit_point, n);
      auto newc = trace(reflected_ray,
                        interval<double>(0.1, interval<double>::infinity));

      ray.set_color(reflected_ray.get_color() * albedo);
      return TraceRecord(true, n);
    }
  }

  auto a = 0.5 * (ray.get_direction().get_z() + 1.0);
  ray.set_color(Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a);
  return TraceRecord::nohit();
}

void RayTracer::render() {
  for (size_t y = 0; y < px_h; y++) {
    for (size_t x = 0; x < px_w; x++) {
      // Get ray for pixel
      auto ray = get_ray(x, y, 0);
      // Trace ray
      
      auto record = trace(ray, interval<double>(0, interval<double>::infinity));
      
      Color color(0, 0, 0);
      color = ray.get_color();

      if (antialiasing) {
        // Antialiasing
        auto d = ray.get_direction();
        auto samples = 10;
        if (samples > 0) {
          color = super_sample(x, y, samples);
        }
      }
      pixels.push_back(color);
      
    }
    std::cerr << (float) (y * px_w) / (px_h *px_w) * 100 << std::endl << std::flush;
  }
}

void RayTracer::dump_image() {
  std::cout << "P3\n" << px_w << " " << px_h << std::endl;
  std::cout << "255" << std::endl;
  for (auto &c : pixels) {
    std::cout << c << std::endl;
  }
}
std::vector<Ray> &RayTracer::get_rays() { return this->rays; }
