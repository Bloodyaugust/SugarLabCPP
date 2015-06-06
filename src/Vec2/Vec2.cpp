#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Vec2.h"

Vec2::Vec2(double x, double y) : x_(x), y_(y) {
}

Vec2* Vec2::clone() {
    return new Vec2(this->x_, this->y_);
}

Vec2* Vec2::direction(Vec2* vector) {
    Vec2* direction_vector = new Vec2(vector->x() - this->x_, vector->y() - this->y_);
    direction_vector->normalize();

    return direction_vector;
}

double Vec2::distance(Vec2* vector) {
    return sqrt(((vector->x() - this->x_) * (vector->x() - this->x_)) + ((vector->y() - this->y_) * (vector->y() - this->y_)));
}

double Vec2::magnitude() {
    return sqrt((this->x_ * this->x_) + (this->y_ * this->y_));
}

double Vec2::angle_between(Vec2* vector) {
    return atan2(this->y_ - vector->y(), this->x_ - vector->x()) * 180 / M_PI;
}

double Vec2::x() const {
    return this->x_;
}

double Vec2::y() const {
    return this->y_;
}

void Vec2::randomize(int max_x, int max_y) {
    this->x_ = rand() % max_x;
    this->y_ = rand() % max_y;
}

void Vec2::translate(Vec2* vector) {
    this->x_ += vector->x();
    this->y_ += vector->y();
}

void Vec2::normalize() {
    double magnitude = this->magnitude();

    this->x_ /= magnitude;
    this->y_ /= magnitude;
}

void Vec2::scale(double scalar) {
    this->x_ *= scalar;
    this->y_ *= scalar;
}

void Vec2::translate_along_angle(double translate_by, double angle) {
    double new_x = translate_by * cos(angle * M_PI / 180);
    double new_y = translate_by * sin(angle * M_PI / 180);

    this->x_ += new_x;
    this->y_ += new_y;
}

void Vec2::rotate(Vec2* origin, double angle) {
    double rotated_x = (this->x_ - origin->x()) * cos(angle * 0.0174532925) - (this->y_ - origin->y()) * sin(angle * 0.0174532925);
    double rotated_y = (this->x_ - origin->x()) * sin(angle * 0.0174532925) + (this->y_ - origin->y()) * cos(angle * 0.0174532925);

    this->x_ = rotated_x + origin->x();
    this->y_ = rotated_y + origin->y();
}

void Vec2::set_x(double x) {
    this->x_ = x;
}

void Vec2::set_y(double y) {
    this->y_ = y;
}
