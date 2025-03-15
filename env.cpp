#include "./include/env.hpp"
#include "./include/utils.hpp"

void Shape::set_texture(std::shared_ptr<Texture> t) {
    texture = t;
}

double Sphere::intersect(Ray &ray, vec3 center) {

    auto v = ray.get_origin() - center;
    // std::cout << v << std::endl;
    auto d = ray.get_direction();
    // std::cout << d << std::endl;
    auto a = std::pow(dot(v, d), 2);
    // std::cout << a << std::endl;
    auto b = dot(v,v) - r * r;
    if (a < b) {
        // std::cout << a << std::endl;
        return -1;
    } else {
        auto sol1 = - dot(v,d) - std::sqrt(a - b);
        auto sol2 = - dot(v,d) + std::sqrt(a - b);
        // std::cout << sol1 << std::endl;
        return std::min(sol1, sol2);
    }
}

void Environment::at(vec3 position, Shape* s) {
    shapes.push_back(std::make_pair(std::unique_ptr<Shape>(s), position));
}

std::vector<std::pair<std::unique_ptr<Shape>, vec3> >& Environment::get_shapes() {
    return shapes;
};


// BasicTexture

Ray BasicTexture::reflected_ray(vec3& hitpoint, vec3& normal, Ray& _) {
    auto reflect_direction = normal + vec3::random_unit();
    auto reflected_ray = Ray(hitpoint, reflect_direction);
    return reflected_ray;
}

Color BasicTexture::attenuation(vec3& hitpoint, vec3& normal) {
    return albedo;
}

// Metal

Ray Metal::reflected_ray(vec3& hitpoint, vec3& normal, Ray& source) {
    auto direction = source.get_direction();
    auto reflect_direction = direction + (- 2) * dot(normal, direction) * normal + fuzz * vec3::random_unit();
    return Ray(hitpoint, reflect_direction);
};

Color Metal::attenuation(vec3& hitpoint, vec3& normal) {
    return albedo;
}