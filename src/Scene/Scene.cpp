#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../src/Actor/Actor.h"
#include "Scene.h"

Scene::Scene(std::string name) : name_(name) {

}

std::vector<Actor*> Scene::get_actors_by_tag(std::string tag) {
    std::vector<Actor*> matching_actors;

    for (int i = 0; i < this->actors_.size(); i++) {
        if (this->actors_[i]->tag() == tag) {
            matching_actors.push_back(this->actors_[i]);
        }
    }

    return matching_actors;
}

std::string Scene::name() {
    return this->name_;
}

void Scene::update(double delta_time) {
    for (int i = 0; i < this->actors_.size(); i++) {
        this->actors_[i]->update(delta_time);
    }
}

void Scene::draw(SDL_Renderer* renderer) {
    SDL_Rect draw_rect;

    for (int i = 0; i < this->actors_.size(); i++) {
        if (this->actors_[i]->draw()) {
            SDL_RenderCopy(renderer, this->actors_[i]->texture(), NULL, this->actors_[i]->draw_rect());
        }
    }
}

void Scene::add_actor(Actor* actor) {
    this->actors_.push_back(actor);
}
