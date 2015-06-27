#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Game.hpp"
#include "Actor.hpp"
#include "Rect.hpp"

class Button : public Actor {
	public:
		explicit Button(std::string text, std::string event, std::string image, Rect* collider, Game* game);

		Rect* collider();
		void update(double delta_time);
		void set_button_hover(Mix_Chunk* sound);

	private:
		Game* game_;
		Mix_Chunk* button_hover_;
		Rect* collider_;
		std::string text_;
		std::string event_;
		std::string state_;
		void generate_draw_rect();
		void generate_src_rect();
};

#endif  // SRC_BUTTON_H_
