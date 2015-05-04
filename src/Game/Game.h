#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <SDL2/SDL.h>

class Game {
    public:
        Game(double window_width_ = 640, double window_height_ = 480);

    	SDL_Window* window() const;
        SDL_Surface* window_surface() const;
        double window_width() const;
        double window_height() const;
        void set_window_width(double width);
        void set_window_height(double height);

    protected:
    	SDL_Window* window_;
        SDL_Surface* window_surface_;
        double window_width_;
        double window_height_;
};

#endif  // SRC_GAME_GAME_H_
