#SugarLab
This is the c++ port of SugarLab.js by Syntactic Sugar Studio.

#Install
./configure (compiling for unix)
./configure --host=i686-w64-mingw32 (compiling for windows)

make && sudo make install

#Linking
You'll need
```
-lsugarlab -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lboost_system -lboost_filesystem
```
to make full use of the library.

#Including
You'll need
```
nclude <sugarlab/Game.hpp>
#include <sugarlab/Scene.hpp>
#include <sugarlab/AssetLoader.hpp>
#include <sugarlab/Rect.hpp>
#include <sugarlab/Vec2.hpp>
#include <sugarlab/Text.hpp>
```
to make full use of the library (not including the boost and sdl headers).
