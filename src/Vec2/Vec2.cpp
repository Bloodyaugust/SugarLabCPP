#include <iostream>
#include "Vec2.h"
using namespace std;

Vec2::Vec2(float x, float y) : x(x), y(y) {
    cout << x << endl;
    cout << y << endl;
}

float Vec2::getX() const {
    return this->x;
}

float Vec2::getY() const {
    return this->y;
}
