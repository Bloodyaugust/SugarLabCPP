#ifndef SRC_ACTOR_ACTOR_H_
#define SRC_ACTOR_ACTOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../src/Vec2/Vec2.h"

class Actor {
    public:
        explicit Actor(std::string tag);

        SDL_Texture* texture();
        SDL_Rect* draw_rect();
        Vec2* position();
        Vec2* texture_size();
        std::string tag();

        bool draw();
        virtual void update(double delta_time);
        void set_texture(SDL_Texture* texture);
        void set_position(Vec2* position);
        void set_draw(bool draw);

    protected:
        SDL_Texture* texture_;
        SDL_Rect* draw_rect_;
        Vec2* position_;
        Vec2* texture_size_;
        std::string tag_;
        bool draw_;
        void generate_draw_rect();
};

#endif  // SRC_ACTOR_ACTOR_H_
