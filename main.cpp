#include "./include/color.hpp"
#include "./include/env.hpp"
#include "./include/tracer.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

void full_image(size_t width, size_t height) {
  std::cout << "P3\n" << width << " " << height << std::endl;
  std::cout << "255" << std::endl;

  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      auto r = 155;
      auto g = 155;
      auto b = 255;
      std::cout << r << ' ' << g << ' ' << b << ' ' << '\n';
      std::clog << y << std::endl << std::flush;
    }
  }
}

int main(int argc, char *argv[]) {
  using namespace std;

  auto to = vec3(0, 100, 0);
  auto from = vec3(-100, 0, 10);

  auto vertical = vec3(0, 0, 1);
  double focus_distance = 150;
  double defocus_angle = 0;

  RayTracer engine(100, 1000, 1000, from, to, vertical, focus_distance,
                   defocus_angle);
  engine.init_rays();

  auto world = std::make_unique<Environment>();

  auto metal = std::shared_ptr<Texture>(
      static_cast<Texture *>(new Metal(Color(0.8, 0.8, 0.8), 0.3)));

  auto basictexture = std::shared_ptr<Texture>(
      static_cast<Texture *>(new BasicTexture(Color(0.6, 0.6, 0.6))));

  auto violet = std::shared_ptr<Texture>(
      static_cast<Texture *>(new BasicTexture(Color(0.7, 0.2, 0.6))));
  

  auto rose = std::shared_ptr<Texture>(
    static_cast<Texture *>(new Metal(Color(0.9, 0.7, 0.9), 0.5)));
  auto s7 = new Sphere(5);
  s7->set_texture(rose);
  world->at(vec3(-80, 40, 5), static_cast<Shape *>(s7));
  
  auto orange = std::shared_ptr<Texture>(
      static_cast<Texture *>(new BasicTexture(Color(0.9, 0.5, 0.1))));
  auto s5 = new Sphere(4);
  s5->set_texture(orange);
  world->at(vec3(2, 90, 4), static_cast<Shape *>(s5));

  
  auto s = new Sphere(10);
  s->set_texture(metal);

  auto s4 = new Sphere(4);
  s4->set_texture(violet);

  auto s3 = new Sphere(10);
  s3->set_texture(metal);

  

  

  world->at(vec3(-25, 100, 10), static_cast<Shape *>(s));
  world->at(vec3(25, 100, 10), static_cast<Shape *>(s3));
  world->at(vec3(0, 100, 4), static_cast<Shape *>(s4));
  

  auto metalfull = std::shared_ptr<Texture>(
    static_cast<Texture *>(new Metal(Color(0.9, 0.9, 0.9), 0)));
  auto s6 = new Sphere(30);
  s6->set_texture(metalfull);
  world->at(vec3(40, 200, 30), static_cast<Shape *>(s6));

  auto s2 = new Sphere(100000);
  s2->set_texture(basictexture);
  world->at(vec3(0, 100, -100000), static_cast<Shape *>(s2));

  engine.set_env(std::move(world));
  engine.render();
  engine.dump_image();
  return 0;
}
