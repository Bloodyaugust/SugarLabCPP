CPP_FILES := src/Game/Game.cpp src/Scene/Scene.cpp src/Actor/Actor.cpp src/Vec2/Vec2.cpp src/AssetLoader.cpp src/Rect.cpp src/Button.cpp src/Collider.cpp src/Text.cpp src/Event.cpp #$(wildcard src/*/*.cpp)
START_FILE := test.cpp

#CC specifies which compiler we're using
CC = g++

LIBRARIES = /lib/boost/

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w  -std=c++11 -pthread

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lboost_system -lboost_filesystem

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = test

#This is the target that compiles our executable
all : $(CPP_FILES)
	$(CC) -I $(LIBRARIES) $(START_FILE) $(CPP_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
