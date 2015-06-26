#include <iostream>
#include "Text.hpp"

Text::Text(std::string text, Rect* rect, TTF_Font* font, SDL_Renderer* renderer) : text_(text), font_(font), renderer_(renderer) {
    this->color_ = {255, 255, 255};

    this->set_rect(rect);
}

void Text::draw() {
    SDL_RenderCopy(this->renderer_, this->texture_, NULL, &this->rect_);
}

void Text::set_text(std::string text) {
    this->text_ = text;
    this->generate_texture();
}

void Text::set_rect(Rect* rect) {
    this->rect_.x = rect->x();
    this->rect_.y = rect->y();
    this->rect_.w = rect->width();
    this->rect_.h = rect->height();
    this->generate_texture();
}

void Text::set_color(SDL_Color color) {
    this->color_ = color;
    this->generate_texture();
}

void Text::generate_texture() {
    SDL_Surface* text_surface = TTF_RenderText_Solid(this->font_, this->text_.c_str(), this->color_);

    this->texture_ = SDL_CreateTextureFromSurface(this->renderer_, text_surface);

    SDL_FreeSurface(text_surface);
}
