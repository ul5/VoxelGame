#pragma once

#include <iostream>
#include "graphics/Window.h"

namespace game {

    class Game {
    private:
        graphics::Window *window;

    public:
        Game();
        ~Game();

        void run();
    };

}