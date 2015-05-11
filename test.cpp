#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "lib/rapidjson/rapidjson.h"
#include "src/Vec2/Vec2.h"
#include "src/Game/Game.h"
#include "src/AssetCollection/AssetCollection.h"
using namespace std;

class App: public Game {
    public:
        App (double window_width, double window_height) : Game (window_width, window_height) {
            cout << "test app constructor" << endl;
            this->test();
        }
        void test () {
            cout << "test app" << endl;
        }
};

int main () {
    cout << "test" << endl << endl;

    App * app = new App(640, 480);

    cout << to_string(app->window_height()) + " " + to_string(app->window_width());

    AssetCollection * assets = new AssetCollection("res/assets.json");

    //game->run();

    cout << endl << endl << "end" << endl;

    return 0;
}
