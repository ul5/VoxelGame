#include <iostream>
#include "graphics/Window.h"

int main(int argc, char **argv) {
    graphics::Window *window = new graphics::Window(); // Initialize all GL stuff

    
    window->run();

    delete window;
    return 0;
}