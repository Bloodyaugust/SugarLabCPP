#ifndef SRC_SCENE_SCENE_H_
#define SRC_SCENE_SCENE_H_

#include "../../src/Actor/Actor.h"
#include <vector>

class Scene {
    public:
        explicit Scene(std::string name);

        std::vector<Actor*> get_actors_by_tag(std::string tag);
        std::string name();
        void update(double delta_time);
        void draw(SDL_Renderer* renderer);
        void add_actor(Actor* actor);

    private:
        std::vector<Actor*> actors_;
        std::string name_;
};

#endif  // SRC_SCENE_SCENE_H_
