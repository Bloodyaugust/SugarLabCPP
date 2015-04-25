#include <iostream>
#include <SDL2/SDL.h>
#include "src/Vec2/Vec2.h"
using namespace std;

int main () {
    cout << "test" << endl;

    Vec2 v1(1, 2);

    cout << v1.getX() << endl;

    return 0;
}
