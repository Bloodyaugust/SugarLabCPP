#ifndef SRC_TEXT_HPP
#define SRC_TEXT_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Rect.hpp"
#include "Vec2/Vec2.h"

class Text {
    public:
        explicit Text(std::string text, Rect* rect, TTF_Font* font, SDL_Renderer* renderer);

        void draw();
        void set_text(std::string text);
        void set_rect(Rect* rect);
        void set_color(SDL_Color color);

    private:
        SDL_Renderer* renderer_;
        SDL_Texture* texture_;
        TTF_Font* font_;
        SDL_Rect rect_;
        std::string text_;
        SDL_Color color_;
        void generate_texture();
};

#endif /* end of include guard: SRC_TEXT_HPP */
