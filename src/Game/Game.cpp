#include "Game.h"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include "../../src/AssetCollection/AssetCollection.h"

Game::Game(double width, double height) : window_width_(width), window_height_(height) {
    std::cout << std::fixed << this->window_width_ << std::endl;
    std::cout << this->window_height_ << std::endl;

    this->start_time_ = std::chrono::system_clock::now();
    this->last_time_ = std::chrono::system_clock::now();

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
        }
    }

    this->is_running_ = true;
}

std::chrono::time_point<std::chrono::system_clock> Game::start_time() {
    return this->start_time_;
}

std::chrono::time_point<std::chrono::system_clock> Game::last_time() {
    return this->last_time_;
}

double Game::window_width() const {
    return this->window_width_;
}

double Game::window_height() const {
    return this->window_height_;
}

double Game::delta_time() {
    return this->delta_time_;
}

void Game::run() {
    std::chrono::time_point<std::chrono::system_clock> new_time;
    std::chrono::duration<double> new_time_ms;

    do {
        new_time = std::chrono::system_clock::now();
        new_time_ms = new_time - this->last_time_;

        this->delta_time_ = new_time_ms.count();

        this->last_time_ = new_time;
    } while (this->is_running_);
}

void Game::update() {

}

void Game::set_window_width(double x) {
    this->window_width_ = x;
}

void Game::set_window_height(double y) {
    this->window_height_ = y;
}
