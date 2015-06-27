#ifndef SRC_SCENE_SCENE_H_
#define SRC_SCENE_SCENE_H_

#include "Actor.hpp"
#include "Event.hpp"
#include <vector>
#include <unordered_map>

class Scene {
    public:
        explicit Scene(std::string name);

        std::vector<Actor*> get_actors_by_tag(std::string tag);
        std::string name();
        virtual void init();
        virtual void update(double delta_time);
        virtual void draw(SDL_Renderer* renderer);
        void add_actor(Actor* actor);
        void emit_event(Event* event);
        void listen_event(std::string event, Actor* listener);

    private:
        std::vector<Actor*> actors_;
        std::vector<Event*> event_queue_;
        std::unordered_map<std::string, std::vector<Actor*>> event_listeners_;
        std::string name_;
};

#endif  // SRC_SCENE_SCENE_H_
