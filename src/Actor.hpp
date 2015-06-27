#ifndef SRC_ACTOR_ACTOR_H_
#define SRC_ACTOR_ACTOR_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vec2.hpp"
#include "Event.hpp"

class Actor {
    public:
        explicit Actor(std::string tag);

        SDL_Texture* texture();
        SDL_Rect* draw_rect();
        SDL_Rect* src_rect();
        Vec2* position();
        Vec2* texture_size();
        std::string tag();
        bool draw();
        virtual void update(double delta_time);
        virtual void emit_event(Event* event);
        void set_texture(SDL_Texture* texture);
        virtual void set_position(Vec2* position);
        void set_draw(bool draw);

    protected:
        SDL_Texture* texture_;
        std::vector<Event*> event_queue_;
        SDL_Rect* draw_rect_;
        SDL_Rect* src_rect_;
        Vec2* position_;
        Vec2* texture_size_;
        std::string tag_;
        bool draw_;
        virtual void generate_draw_rect();
        virtual void generate_src_rect();
};

#endif  // SRC_ACTOR_ACTOR_H_
