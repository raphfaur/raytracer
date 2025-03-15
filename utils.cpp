#include "./include/utils.hpp"

vec3 random_hemisphere_direction(vec3 normal) {
    auto v = vec3::random_unit();
    if (dot(v, normal) < 0) {
        return -1 * v;
    } else {
        return v;
    }
}



double random_double(double min, double max){
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

double degre_to_radian(double angle) {
    return angle * pi / 180 ;
}