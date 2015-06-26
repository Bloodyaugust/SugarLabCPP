#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../src/Vec2/Vec2.h"
#include "Actor.h"

Actor::Actor(std::string tag) : tag_(tag) {
    this->position_ = new Vec2(0, 0);
    this->draw_ = false;

    this->draw_rect_ = new SDL_Rect {0, 0, 0, 0};
    this->src_rect_ = new SDL_Rect {0, 0, 0, 0};

    this->texture_size_ = new Vec2(0, 0);
}

SDL_Texture* Actor::texture() {
    return this->texture_;
}

SDL_Rect* Actor::draw_rect() {
    return this->draw_rect_;
}

SDL_Rect* Actor::src_rect() {
    return this->src_rect_;
}

Vec2* Actor::position() {
    return this->position_;
}

Vec2* Actor::texture_size() {
    return this->texture_size_;
}

std::string Actor::tag() {
    return this->tag_;
}

bool Actor::draw() {
    return this->draw_;
}

void Actor::update(double delta_time) {
    if (this->draw_rect_->x != this->position_->x()) {
        this->generate_draw_rect();
    } else if (this->draw_rect_->y != this->position_->y()) {
        this->generate_draw_rect();
    }
}

void Actor::emit_event(Event* event) {
    this->event_queue_.push_back(event);
}

void Actor::generate_draw_rect() {
    this->draw_rect_->x = this->position_->x();
    this->draw_rect_->y = this->position_->y();
    this->draw_rect_->w = this->texture_size_->x();
    this->draw_rect_->h = this->texture_size_->y();
}

void Actor::generate_src_rect() {
    this->src_rect_->x = 0;
    this->src_rect_->y = 0;
    this->src_rect_->w = this->texture_size_->x();
    this->src_rect_->h = this->texture_size_->y();
}

void Actor::set_texture(SDL_Texture* texture) {
    int width, height;

    this->texture_ = texture;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    this->texture_size_ = new Vec2(width, height);

    this->generate_draw_rect();
    this->generate_src_rect();

    this->draw_ = true;
}

void Actor::set_position(Vec2* position) {
    this->position_ = position;

    this->generate_draw_rect();
}

void Actor::set_draw(bool draw) {
    this->draw_ = draw;
}
