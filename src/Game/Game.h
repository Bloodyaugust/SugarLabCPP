#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <SDL2/SDL.h>
#include <chrono>
#include "../../src/AssetCollection/AssetCollection.h"

class Game {
    public:
        explicit Game(double window_width_ = 640, double window_height_ = 480);

    	SDL_Window* window() const;
        SDL_Surface* window_surface() const;
        std::chrono::time_point<std::chrono::system_clock> start_time();
        std::chrono::time_point<std::chrono::system_clock> last_time();
        double window_width() const;
        double window_height() const;
        double delta_time();
        void run();
        void update();
        void set_window_width(double width);
        void set_window_height(double height);

    protected:
    	SDL_Window* window_;
        SDL_Surface* window_surface_;
        std::chrono::time_point<std::chrono::system_clock> start_time_;
        std::chrono::time_point<std::chrono::system_clock> last_time_;
        double window_width_;
        double window_height_;
        double delta_time_;
        bool is_running_;
};

#endif  // SRC_GAME_GAME_H_
