#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Collider.hpp"

Collider::Collider(Rect* rect) : collider_rect_(rect) {
    this->type_ = "rect";
}

bool Collider::intersects(Rect* rect) {
    bool result;

    if (this->type_ == "rect") {
        result = this->collider_rect_->intersects(rect);
    } else {
        result = false;
    }

    return result;
}
