#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Actor.hpp"
#include "Scene.hpp"

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

void Scene::init() {

}

void Scene::update(double delta_time) {
    for (int i = 0; i < this->event_queue_.size(); i++) {
        std::vector<Actor*> current_event_listeners = this->event_listeners_[this->event_queue_[i]->type()];

        for (int i2 = 0; i2 < current_event_listeners.size(); i2++) {
            current_event_listeners[i2]->emit_event(this->event_queue_[i]);
        }
    }
    this->event_queue_.clear();

    for (int i = 0; i < this->actors_.size(); i++) {
        this->actors_[i]->update(delta_time);
    }
}

void Scene::draw(SDL_Renderer* renderer) {
    SDL_Rect draw_rect;

    for (int i = 0; i < this->actors_.size(); i++) {
        if (this->actors_[i]->draw()) {
            SDL_RenderCopy(renderer, this->actors_[i]->texture(), this->actors_[i]->src_rect(), this->actors_[i]->draw_rect());
        }
    }
}

void Scene::add_actor(Actor* actor) {
    this->actors_.push_back(actor);
}

void Scene::emit_event(Event* event) {
    this->event_queue_.push_back(event);
}

void Scene::listen_event(std::string event, Actor* listener) {
    this->event_listeners_[event].push_back(listener);
}
