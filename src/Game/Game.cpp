#include <iostream>
#include <stdio.h>
#include "Game.h"

Game::Game(double width, double height) : window_width_(width), window_height_(height) {
    std::cout << this->window_width_ << std::endl;
    std::cout << this->window_height_ << std::endl;

    this->window_ = NULL;
    this->window_surface_ = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        this->window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->window_width_, this->window_height_, SDL_WINDOW_SHOWN);
        if (this->window_ == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            this->window_surface_ = SDL_GetWindowSurface(this->window_);
            SDL_FillRect(this->window_surface_, NULL, SDL_MapRGB(this->window_surface_->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(this->window_);
            SDL_Delay(2000);
        }
    }
}

double Game::window_width() const {
    return this->window_width_;
}

double Game::window_height() const {
    return this->window_height_;
}

void Game::set_window_width(double x) {
    this->window_width_ = x;
}

void Game::set_window_height(double y) {
    this->window_height_ = y;
}
