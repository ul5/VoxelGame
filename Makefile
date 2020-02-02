CXX = g++
OBJS = graphics/Window.o graphics/BlockMesh.o graphics/Shader.o util/ReadFile.o game/Game.o world/Block.o world/Chunk.o world/World.o  main.o
CXX_OPTS = -std=c++11 -Wall -Wextra -Wunused -O2 -g
INCLUDES = -Isrc -Ilib/glew-2.1.0/include/ -Ilib/glfw-3.3.2/include/ -Ilib/glm/ -isystem lib/stb
LIBS = -Llib/glfw-3.3.2/src/ -Llib/glew-2.1.0/lib -lglfw -lGLEW

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBS += -framework OpenGL
endif
ifeq ($(UNAME_S),Linux)
	LIBS += -lGL
endif

BUILD_OBJS = $(foreach obj, $(OBJS), build/$(obj))

all: setup voxelgame

setup: clean
	echo $(BUILD_OBJS)
	-mkdir build
	-mkdir build/graphics
	-mkdir build/util
	-mkdir build/world
	-mkdir build/game

clean:
	-rm -r build/

voxelgame: $(BUILD_OBJS)
	$(CXX) $(CXX_OPTS) $(LIBS) $(BUILD_OBJS) $(LIBS) -o voxelgame

build/%.o: src/%.cpp
	$(CXX) $(CXX_OPTS) $(INCLUDES) -c $< -o $@
