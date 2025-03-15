#pragma once
#include "vec3.hpp"
#include <random>
#include<numbers>

template<typename t>
class interval {
public :
    t min;
    t max;

    interval(t min, t max) : min(min), max(max) {}

    static t clamp(interval& i, t value) {
        if (value > i.max) {
            return i.max;
        } else {
            if (value < i.min ) {
                return i.min;
            }
        }
    }

    bool contains(t value) {
        return (value >= min && value <= max);
    } 
    
    static constexpr double infinity = std::numeric_limits<t>::infinity();
};

double random_double(double min, double max);
vec3 random_hemisphere_direction(vec3 normal);

const static double pi = 3.141592653589;

double degre_to_radian(double angle);
