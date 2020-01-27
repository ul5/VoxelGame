CXX = g++
OBJS =graphics/Window.o graphics/Shader.o util/ReadFile.o  main.o
CXX_OPTS = -std=c++11
INCLUDES = -Isrc -Ilib/glew-2.1.0/include/ -Ilib/glfw-3.3.2/include/
LIBS = -Llib/glfw-3.3.2/src/ -lglfw -Llib/glew-2.1.0/lib -lGLEW

BUILD_OBJS = $(foreach obj, $(OBJS), build/$(obj))

all: setup voxelgame

setup: clean
	echo $(BUILD_OBJS)
	-mkdir build
	-mkdir build/graphics
	-mkdir build/util

clean:
	-rm -r build/

voxelgame: $(BUILD_OBJS)
	$(CXX) $(CXX_OPTS) $(LIBS) $(BUILD_OBJS) $(LIBS) -o voxelgame

build/%.o: src/%.cpp
	$(CXX) $(CXX_OPTS) $(INCLUDES) $(LIBS) -c $< -o $@
