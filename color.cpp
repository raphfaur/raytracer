#include"./include/color.hpp"

int linear_to_gamma(int intensity) {
    return std::sqrt(intensity);
}

Color operator* (const Color& c1, const Color& c2) {
    return Color(c1.get_x() * c2.get_x(), c1.get_y() * c2.get_y(), c1.get_z() * c2.get_z());
}