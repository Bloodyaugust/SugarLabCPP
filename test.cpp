#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "src/Vec2/Vec2.h"
#include "src/Game/Game.h"
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
    cout << "test" << endl;

    Vec2 v1(1, 2);

    v1.set_x(3);

    cout << to_string(v1.x()) + " " + to_string(v1.y()) << endl;

    App game(640, 480);

    cout << to_string(game.window_height()) + " " + to_string(game.window_width());

    return 0;
}
