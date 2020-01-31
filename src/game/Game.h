#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "graphics/Window.h"
#include "world/World.h"

namespace game {

    extern void game_render(void *game_ptr, graphics::Window *window);

    class Game {
    private:
        graphics::Window *window = nullptr;
        graphics::Shader *shader = nullptr;

        graphics::ShaderUniform *u_time = nullptr, *u_camera = nullptr, *u_rotation = nullptr, *u_sampler = nullptr;

        world::World *game_world = nullptr;

        float cur_time = 0.0f;
        glm::vec3 camera = glm::vec3(0, -64, 0);
        glm::vec3 rotation = glm::vec3(0, 0, 0);

        void render(graphics::Window *window);
        friend void game::game_render(void *game_ptr, graphics::Window *window);

    public:
        Game();
        ~Game();

        void run();
    };

}