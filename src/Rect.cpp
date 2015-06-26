#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Rect.hpp"

Rect::Rect(double x, double y, double width, double height) : x_(x), y_(y), width_(width), height_(height) {
    this->x2_ = this->x_ + this->width_;
    this->y2_ = this->y_ + this->height_;
}
Rect::Rect(Vec2* position, Vec2* size) {
    this->x_ = position->x();
    this->y_ = position->y();
    this->width_ = size->x();
    this->height_ = size->y();
    this->x2_ = this->x_ + this->width_;
    this->y2_ = this->y_ + this->height_;
}

Rect* Rect::clone() {
    return new Rect(this->x_, this->y_, this->width_, this->height_);
}

double Rect::x() {
    return this->x_;
}

double Rect::y() {
    return this->y_;
}

double Rect::x2() {
    return this->x2_;
}

double Rect::y2() {
    return this->y2_;
}

double Rect::width() {
    return this->width_;
}

double Rect::height() {
    return this->height_;
}

bool Rect::intersects(Rect* rect) {
    return (this->x_ < rect->x2() && this->x2_ > rect->x() && this->y_ < rect->y2() && this->y2_ > rect->y());
}

void Rect::translate(Vec2* vector) {
    this->x_ += vector->x();
    this->y_ += vector->y();
    this->x2_ = this->x_ + this->width_;
    this->y2_ = this->y_ + this->height_;
}
void Rect::translate(double x, double y) {
    this->x_ += x;
    this->y_ += y;
    this->x2_ = this->x_ + this->width_;
    this->y2_ = this->y_ + this->height_;
}

void Rect::scale(double scalar) {
    this->width_ *= scalar;
    this->height_ *= scalar;
    this->x2_ = this->x_ + this->width_;
    this->y2_ = this->y_ + this->height_;
}

void Rect::set_x(double x) {
    this->x_ = x;
    this->x2_ = x + this->width_;
}

void Rect::set_y(double y) {
    this->y_ = y;
    this->y2_ = y + this->height_;
}

void Rect::set_width(double width) {
    this->width_ = width;
    this->x2_ = this->x_ + this->width_;
}

void Rect::set_height(double height) {
    this->height_ = height;
    this->y2_ = this->y_ + this->height_;
}
