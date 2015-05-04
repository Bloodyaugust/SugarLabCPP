CPP_FILES := $(wildcard src/*/*.cpp)
START_FILE := test.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w  -std=c++0x

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = test

#This is the target that compiles our executable
all : $(CPP_FILES)
	$(CC) $(START_FILE) $(CPP_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
