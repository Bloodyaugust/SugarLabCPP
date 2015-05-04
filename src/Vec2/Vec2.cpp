#include <iostream>
#include "Vec2.h"

Vec2::Vec2(double x, double y) : x_(x), y_(y) {
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

double Vec2::x() const {
    return this->x_;
}

double Vec2::y() const {
    return this->y_;
}

void Vec2::set_x(double x) {
    this->x_ = x;
}

void Vec2::set_y(double y) {
    this->y_ = y;
}
