#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include <boost/filesystem.hpp>
#include "lib/rapidjson/rapidjson.h"
#include "src/Vec2/Vec2.h"
#include "src/Game/Game.h"
#include "src/AssetCollection/AssetCollection.h"
#include "src/ImageLoader/ImageLoader.h"
#include "src/Scene/Scene.h"
#include "src/Actor/Actor.h"
using namespace std;
using namespace boost::filesystem;

class App: public Game {
    public:
        App (double window_width, double window_height) : Game (window_width, window_height) {
            this->test();
        }
        void test() {

        }
};

class Fireball: public Actor {
    public:
        Fireball (string tag) : Actor (tag) {
            this->velocity_ = new Vec2(0, 0);
            this->velocity_->randomize(500, 500);
        }
        void update(double delta_time) {
            Actor::update(delta_time);

            if (this->position_->x() < 0) {
                this->velocity_->set_x(abs(this->velocity_->x()));
            } else if (this->position_->x() > 1200) {
                this->velocity_->set_x(this->velocity_->x() * -1);
            }
            if (this->position_->y() < 0) {
                this->velocity_->set_y(abs(this->velocity_->y()));
            } else if (this->position_->y() > 900) {
                this->velocity_->set_y(this->velocity_->y() * -1);
            }

            this->position_->set_x(this->position_->x() + this->velocity_->x() * delta_time);
            this->position_->set_y(this->position_->y() + this->velocity_->y() * delta_time);
        }

    private:
        Vec2 * velocity_;
};

class Loader: public Actor {
    public:
        Loader(string tag) : Actor(tag) {

        }

};

int main() {
    cout << "test" << endl << endl;

    App * app = new App(1280, 1020);

    cout << to_string(app->window_height()) + " " + to_string(app->window_width()) << endl;

    ImageLoader * images = new ImageLoader("res/img/", app->window_renderer());

    Scene* load_scene = new Scene("load");
    Actor* load_data = new Actor("loader");


    Scene * test_scene = new Scene("test");

    for (int i = 0; i < 100; i++) {
        Fireball * test_actor = new Fireball("tester");
        Vec2 * random_position = new Vec2(0, 0);
        random_position->randomize(600, 500);

        test_actor->set_texture(images->get_texture("fireball.png"));
        test_actor->set_position(random_position);

        test_scene->add_actor(test_actor);
    }

    app->add_scene(test_scene);
    app->set_scene("test");

    app->run();

    cout << endl << endl << "end" << endl;

    return 0;
}
