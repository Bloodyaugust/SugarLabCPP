#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <SDL2/SDL.h>
#include <chrono>
#include <array>
#include "../../src/AssetCollection/AssetCollection.h"
#include "../../src/Scene/Scene.h"

class Game {
    public:
        explicit Game(double window_width_ = 640, double window_height_ = 480);

        Scene* active_scene();
      	SDL_Window* window() const;
        SDL_Renderer* window_renderer() const;
        std::chrono::time_point<std::chrono::system_clock> start_time();
        std::chrono::time_point<std::chrono::system_clock> last_time();
        double window_width() const;
        double window_height() const;
        double delta_time();
        double fps();
        void run();
        void update();
        void draw();
        void add_scene(Scene* scene);
        void set_scene(std::string scene_name);
        void set_window_width(double width);
        void set_window_height(double height);

    protected:
        Scene* active_scene_;
      	SDL_Window* window_;
        SDL_Renderer* window_renderer_;
        std::chrono::time_point<std::chrono::system_clock> start_time_;
        std::chrono::time_point<std::chrono::system_clock> last_time_;
        std::array<Scene*, 99> scenes_;
        int scene_count_;
        double window_width_;
        double window_height_;
        double delta_time_;
        double fps_;
        double fps_timer_;
        double fps_counter_;
        bool is_running_;
};

#endif  // SRC_GAME_GAME_H_
