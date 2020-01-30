CXX = g++
OBJS = graphics/Window.o graphics/Shader.o graphics/VertexBuffer.o util/ReadFile.o game/Game.o world/Block.o world/Chunk.o world/World.o  main.o
CXX_OPTS = -std=c++11 -Wall -Wextra -Wunused
INCLUDES = -Isrc -Ilib/glew-2.1.0/include/ -Ilib/glfw-3.3.2/include/ -Ilib/glm/
LIBS = -Llib/glfw-3.3.2/src/ -Llib/glew-2.1.0/lib -lglfw -lGLEW -lGL

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
	$(CXX) $(CXX_OPTS) $(INCLUDES) -c $< -o $@ $(LIBS)
