#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <array>
#include <unordered_map>
#include "../../src/Scene/Scene.h"
#include "../../src/AssetLoader.hpp"
#include "../../src/Vec2/Vec2.h"

class Game {
    public:
        explicit Game(double window_width_ = 640, double window_height_ = 480);

        Scene* active_scene();
        AssetLoader* assets();
      	SDL_Window* window() const;
        SDL_Renderer* window_renderer() const;
        std::chrono::time_point<std::chrono::system_clock> start_time();
        std::chrono::time_point<std::chrono::system_clock> last_time();
        Vec2* native_resolution();
        Vec2* mouse_position();
        double window_width() const;
        double window_height() const;
        double x_scalar();
        double y_scalar();
        double delta_time();
        double fps();
        bool key_down(int key);
        bool on_key_down(int key);
        bool on_key_up(int key);
        bool mouse_down(int mouse_button);
        bool on_mouse_down(int mouse_button);
        bool on_mouse_up(int mouse_button);
        void run();
        void update();
        void draw();
        void add_scene(Scene* scene);
        void set_asset_loader(std::string image_path, std::string sfx_path);
        void set_scene(std::string scene_name);
        void set_native_resolution(Vec2* resolution);
        void set_window_width(double width);
        void set_window_height(double height);
        void set_window_clear_color(int r, int g, int b);

    protected:
        Scene* active_scene_;
        AssetLoader* assets_;
        SDL_Window* window_;
        SDL_Renderer* window_renderer_;
        std::unordered_map<int, int> key_states_;
        std::unordered_map<int, int> mouse_states_;
        std::unordered_map<std::string, Scene*> scenes_;
        std::chrono::time_point<std::chrono::system_clock> start_time_;
        std::chrono::time_point<std::chrono::system_clock> last_time_;
        Vec2* native_resolution_;
        Vec2* mouse_position_;
        double window_width_;
        double window_height_;
        double x_scalar_;
        double y_scalar_;
        double delta_time_;
        double fps_;
        double fps_timer_;
        double fps_counter_;
        double time_since_last_render_;
        bool is_running_;
        bool scene_initialized_;
        bool is_fullscreen_;
        void get_window_size();
};

#endif  // SRC_GAME_GAME_H_
