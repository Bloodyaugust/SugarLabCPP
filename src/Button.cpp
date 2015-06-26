#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include "Button.hpp"

Button::Button(std::string text, std::string event, std::string image, Rect* collider, Game* game) : text_(text), event_(event), collider_(collider), game_(game), Actor("button") {
    this->set_texture(this->game_->assets()->texture(image));

    this->state_ = "idle";
    this->button_hover_ = NULL;

    generate_draw_rect();
}

Rect* Button::collider() {
    return this->collider_;
}

void Button::update(double delta_time) {
    Vec2* mouse_rect_size = new Vec2(1, 1);
    Vec2* mouse_position = this->game_->mouse_position();
    Rect* mouse_rect = new Rect(mouse_position, mouse_rect_size);

    if (this->collider_->intersects(mouse_rect)) {
        if (this->state_ == "idle" && this->button_hover_ != NULL) {
            Mix_PlayChannel(-1, this->button_hover_, 0);
        }
        this->state_ = "active";

        if (this->game_->on_mouse_up(SDL_BUTTON_LEFT)) {
            this->game_->active_scene()->emit_event(new Event(this->event_, "press"));
        }
    } else {
        this->state_ = "idle";
    }

    this->generate_src_rect();
    this->generate_draw_rect();
}

void Button::set_button_hover(Mix_Chunk* sound) {
    this->button_hover_ = sound;
}

void Button::generate_draw_rect() {
    this->draw_rect_->x = this->collider_->x() * this->game_->x_scalar();
    this->draw_rect_->y = this->collider_->y() * this->game_->y_scalar();
    this->draw_rect_->w = this->collider_->width() * this->game_->x_scalar();
    this->draw_rect_->h = this->collider_->height() * this->game_->y_scalar();
}

void Button::generate_src_rect() {
    if (this->state_ == "idle") {
        this->src_rect_->x = 0;
        this->src_rect_->y = 0;
        this->src_rect_->w = this->collider_->width();
        this->src_rect_->h = this->collider_->height();
    } else {
        this->src_rect_->x = this->collider_->width();
        this->src_rect_->y = 0;
        this->src_rect_->w = this->collider_->width();
        this->src_rect_->h = this->collider_->height();
    }
}
