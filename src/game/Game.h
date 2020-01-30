#pragma once

#include <iostream>
#include "graphics/Window.h"

namespace game {

    extern void game_render(void *game_ptr, graphics::Window *window);

    class Game {
    private:
        graphics::Window *window = nullptr;
        graphics::VertexBuffer *vb = nullptr;
        graphics::Shader *shader = nullptr;

        graphics::ShaderUniform *u_time = nullptr, *u_camera = nullptr, *u_rotation = nullptr;

        float cur_time = 0.0f;
        float angle = 0.0f;
        glm::vec3 camera = glm::vec3(0, 0, 0);
        glm::vec3 rotation = glm::vec3(0, 0, 0);

        void render(graphics::Window *window);
        friend void game::game_render(void *game_ptr, graphics::Window *window);

    public:
        Game();
        ~Game();

        void run();
    };

}