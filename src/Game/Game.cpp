#include "Game.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include <chrono>
#include "../../src/AssetCollection/AssetCollection.h"
#include "../../src/Scene/Scene.h"

Game::Game(double width, double height) : window_width_(width), window_height_(height) {
    std::cout << std::fixed << this->window_width_ << std::endl;
    std::cout << this->window_height_ << std::endl;

    this->start_time_ = std::chrono::system_clock::now();
    this->last_time_ = std::chrono::system_clock::now();

    this->window_ = NULL;
    this->window_renderer_ = NULL;

    this->fps_ = 0;
    this->fps_counter_ = 0;
    this->fps_timer_ = 0;

    this->scene_count_ = 0;
    this->active_scene_ = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        this->window_ = SDL_CreateWindow("SugarLab", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->window_width_, this->window_height_, SDL_WINDOW_SHOWN);
        if (this->window_ == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            this->window_renderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED);
            if(this->window_renderer_ == NULL) {
                std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
            } else {
                SDL_SetRenderDrawColor(this->window_renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                  std::cout << "SDL_Image could not initialize: " << IMG_GetError() << std::endl;
                }
            }
        }
    }

    this->is_running_ = true;
}

Scene* Game::active_scene() {
    return this->active_scene_;
}

SDL_Window* Game::window() const {
    return this->window_;
}

SDL_Renderer* Game::window_renderer() const {
    return this->window_renderer_;
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

double Game::fps() {
    return this->fps_;
}

void Game::run() {
    SDL_Event e;

    std::chrono::time_point<std::chrono::system_clock> new_time;
    std::chrono::duration<double> new_time_ms;

    do {
        new_time = std::chrono::system_clock::now();
        new_time_ms = new_time - this->last_time_;

        this->delta_time_ = new_time_ms.count();

        this->last_time_ = new_time;

        while(SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            this->is_running_ = false;
          }
        }

        this->update();
    } while (this->is_running_);
}

void Game::update() {
    this->fps_timer_ += this->delta_time_;
    this->fps_counter_ += 1;

    if (this->fps_timer_ >= 1) {
        this->fps_ = this->fps_counter_;

        std::cout << "FPS: " << this->fps_counter_ << std::endl;

        this->fps_counter_ = 0;
        this->fps_timer_ = 0;
    }

    this->active_scene_->update(this->delta_time_);
    this->draw();
}

void Game::draw() {
    SDL_RenderClear(this->window_renderer_);

    this->active_scene_->draw(this->window_renderer_);

    SDL_RenderPresent(this->window_renderer_);
}

void Game::add_scene(Scene* scene) {
    this->scenes_[this->scene_count_] = scene;
    this->scene_count_++;
    std::cout << "Scene added: " << scene->name() << std::endl;
}

void Game::set_scene(std::string scene_name) {
    for (int i = 0; i < this->scene_count_; i++) {
        if (this->scenes_[i]->name() == scene_name) {
            this->active_scene_ = this->scenes_[i];
            std::cout << "Switching to scene: " << scene_name << std::endl;
            break;
        }
    }
}

void Game::set_window_width(double x) {
    this->window_width_ = x;
}

void Game::set_window_height(double y) {
    this->window_height_ = y;
}
