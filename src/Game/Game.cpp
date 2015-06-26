#include "Game.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <array>
#include <chrono>
#include "../../src/Scene/Scene.h"

Game::Game(double width, double height) : window_width_(width), window_height_(height) {
    std::cout << std::fixed << this->window_width_ << std::endl;
    std::cout << this->window_height_ << std::endl;

    this->start_time_ = std::chrono::system_clock::now();
    this->last_time_ = std::chrono::system_clock::now();

    this->mouse_position_ = new Vec2(0, 0);

    this->window_ = NULL;
    this->window_renderer_ = NULL;

    this->is_fullscreen_ = false;

    this->fps_ = 0;
    this->fps_counter_ = 0;
    this->fps_timer_ = 0;

    this->scene_initialized_ = false;
    this->active_scene_ = NULL;

    this->native_resolution_ = new Vec2(this->window_width_, this->window_height_);
    this->x_scalar_ = 1;
    this->y_scalar_ = 1;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
        this->window_ = SDL_CreateWindow("SugarLab | Syntactic Sugar Studio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->window_width_, this->window_height_, SDL_WINDOW_SHOWN);
        if (this->window_ == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
          this->window_renderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(this->window_renderer_ == NULL) {
                std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
            } else {
                SDL_SetRenderDrawColor(this->window_renderer_, 0, 255, 0, 255);

                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    std::cout << "SDL_Image could not initialize: " << IMG_GetError() << std::endl;
                } else {
                    std::cout << "SDL_Image initialized" << std::endl;
                }
            }
        }
    }

    if (TTF_Init() < 0) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    } else {
        std::cout << "SDL_ttf initialized" << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "SDL_mixer initialized" << std::endl;
    }

    this->is_running_ = true;
}

Scene* Game::active_scene() {
    return this->active_scene_;
}

AssetLoader* Game::assets() {
    return this->assets_;
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

Vec2* Game::mouse_position() {
    return this->mouse_position_;
}

Vec2* Game::native_resolution() {
    return this->native_resolution_;
}

double Game::window_width() const {
    return this->window_width_;
}

double Game::window_height() const {
    return this->window_height_;
}

double Game::x_scalar() {
    return this->x_scalar_;
}

double Game::y_scalar() {
    return this->y_scalar_;
}

double Game::delta_time() {
    return this->delta_time_;
}

double Game::fps() {
    return this->fps_;
}

bool Game::key_down(int key) {
    return this->key_states_[key] > 0 ? true : false;
}

bool Game::on_key_down(int key) {
    return this->key_states_[key] == 1 ? true : false;
}

bool Game::on_key_up(int key) {
    return this->key_states_[key] == -1 ? true : false;
}

bool Game::mouse_down(int mouse_button) {
    return this->mouse_states_[mouse_button] > 0 ? true : false;
}

bool Game::on_mouse_down(int mouse_button) {
    return this->mouse_states_[mouse_button] == 1 ? true : false;
}

bool Game::on_mouse_up(int mouse_button) {
    return this->mouse_states_[mouse_button] == -1 ? true : false;
}

void Game::run() {
    SDL_Event e;

    std::chrono::time_point<std::chrono::system_clock> new_time;
    std::chrono::duration<double> new_time_ms;

    int mouse_x, mouse_y;

    if (this->assets_ != NULL) {
        this->assets_->load();
    }

    do {
        new_time = std::chrono::system_clock::now();
        new_time_ms = new_time - this->last_time_;

        this->delta_time_ = new_time_ms.count();

        this->last_time_ = new_time;
        this->time_since_last_render_ += this->delta_time_;

        for (auto i = this->key_states_.begin(); i != this->key_states_.end(); i++) {
            if (this->key_states_[i->first] != 0) {
                this->key_states_[i->first] += 1;
            }
        }

        for (auto i = this->mouse_states_.begin(); i != this->mouse_states_.end(); i++) {
            if (this->mouse_states_[i->first] != 0) {
                this->mouse_states_[i->first] += 1;
            }
        }

        while(SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    this->is_running_ = false;
                    break;

                case SDL_KEYDOWN:
                    this->key_states_[e.key.keysym.sym] = this->key_states_[e.key.keysym.sym] > 1 ? this->key_states_[e.key.keysym.sym] : 1;
                    break;

                case SDL_KEYUP:
                    this->key_states_[e.key.keysym.sym] = -1;
                    break;

                case SDL_WINDOWEVENT:
                    switch (e.window.event) {
                      case SDL_WINDOWEVENT_RESIZED:
                          this->get_window_size();
                          this->active_scene_->emit_event(new Event("resize", std::to_string(this->window_width_) + "x" + std::to_string(this->window_height_)));
                          break;

                      default:
                          break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    this->mouse_states_[e.button.button] = this->mouse_states_[e.button.button] > 1 ? this->mouse_states_[e.button.button] : 1;
                    break;

                case SDL_MOUSEBUTTONUP:
                    this->mouse_states_[e.button.button] = -1;
                    break;

                default:
                    break;
            }
        }

        SDL_GetMouseState(&mouse_x, &mouse_y);
        this->mouse_position_->set_x(mouse_x);
        this->mouse_position_->set_y(mouse_y);

        if (!this->scene_initialized_) {
            this->active_scene_->init();
            this->scene_initialized_ = true;
        }

        if (this->on_key_up(SDLK_F11)) {
            if (!this->is_fullscreen_) {
                SDL_SetWindowFullscreen(this->window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
                this->is_fullscreen_ = true;
            } else {
                SDL_SetWindowFullscreen(this->window_, 0);
                this->is_fullscreen_ = false;
            }
        }

        if ((this->key_down(SDLK_LCTRL) || this->key_down(SDLK_RCTRL)) && this->key_down(SDLK_q)) {
            this->is_running_ = false;
        }

        this->update();
    } while (this->is_running_);

    SDL_DestroyRenderer(this->window_renderer_);
    SDL_DestroyWindow(this->window_);
    this->window_renderer_ = NULL;
    this->window_ = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::update() {
    this->fps_timer_ += this->delta_time_;
    this->fps_counter_ += 1;

    if (this->fps_timer_ >= 1) {
        this->fps_ = this->fps_counter_;

        //std::cout << "FPS: " << this->fps_counter_ << std::endl;

        this->fps_counter_ = 0;
        this->fps_timer_ = 0;
    }

    if (this->active_scene_ != NULL) {
        this->active_scene_->update(this->delta_time_);

        if (this->time_since_last_render_ >= 0.016666666666666666) {
            this->draw();
            this->time_since_last_render_ = 0;
        }
    }
}

void Game::draw() {
    SDL_RenderClear(this->window_renderer_);

    this->active_scene_->draw(this->window_renderer_);

    SDL_RenderPresent(this->window_renderer_);
}

void Game::add_scene(Scene* scene) {
    this->scenes_[scene->name()] = scene;
}

void Game::set_asset_loader(std::string image_path, std::string sfx_path) {
    this->assets_ = new AssetLoader(image_path, sfx_path, this->window_renderer_);
}

void Game::set_scene(std::string scene_name) {
    this->active_scene_ = this->scenes_[scene_name];
    this->scene_initialized_ = false;
}

void Game::set_native_resolution(Vec2* resolution) {
    this->native_resolution_ = resolution->clone();
}

void Game::set_window_width(double x) {
    this->window_width_ = x;
}

void Game::set_window_height(double y) {
    this->window_height_ = y;
}

void Game::set_window_clear_color(int r, int g, int b) {
    SDL_SetRenderDrawColor(this->window_renderer_, r, g, b, 255);
}

void Game::get_window_size() {
    int width, height;
    SDL_GetWindowSize(this->window_, &width, &height);

    this->window_width_ = width;
    this->window_height_ = height;

    this->x_scalar_ = this->window_width_ / this->native_resolution_->x();
    this->y_scalar_ = this->window_height_ / this->native_resolution_->y();
}
