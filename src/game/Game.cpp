#include "Game.h"

void game::game_render(void *game_ptr, graphics::Window *window) {
    game::Game *g = (game::Game*) game_ptr;
    g->render(window);
}

game::Game::Game() {
    window = new graphics::Window(); // Initialize all GL stuffs

    shader = graphics::loadShaderFromFiles("res/shaders/basic.vert", "res/shaders/basic.frag");
    u_time = shader->getUniform("time");
    u_camera = shader->getUniform("camera");
    u_rotation = shader->getUniform("rotation");
    u_lookingat = shader->getUniform("looking_at");

    u_sampler = shader->getUniform("tex");
    u_sampler->update1i(0);

    game_world = new world::World();

    window->addRenderFunc(game::game_render, this);
}

void game::Game::render(graphics::Window *window) {
    if(window->isKeyPressed(GLFW_KEY_ESCAPE)) window->closeWindow();
    shader->use();

    glm::dvec2 mouse_pos = window->getMousePos();
    rotation.y -= mouse_pos.x / 500.0;
    rotation.x -= mouse_pos.y / 500.0;
    if(rotation.x < -M_PI / 2.0) rotation.x = -M_PI / 2.0;
    if(rotation.x > M_PI / 2.0) rotation.x = M_PI / 2.0;

    float ws = 0.0f, ad = 0.0f;

    if(window->isKeyPressed(GLFW_KEY_W)) ws += 0.1f;
    if(window->isKeyPressed(GLFW_KEY_S)) ws -= 0.1f;
    if(window->isKeyPressed(GLFW_KEY_D)) ad -= 0.1f;
    if(window->isKeyPressed(GLFW_KEY_A)) ad += 0.1f;
    if(window->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) camera.y += 0.1f;
    if(window->isKeyPressed(GLFW_KEY_SPACE)) camera.y -= 0.1f;

    camera.z += cos(rotation.y) * ws - sin(rotation.y) * ad;
    camera.x += cos(rotation.y) * ad + sin(rotation.y) * ws;

    glm::vec3 dir = glm::vec3(-cos(rotation.x) * sin(rotation.y), sin(rotation.x), -cos(rotation.x) * cos(rotation.y));
    dir = normalize(dir) / 5.0f;
    for(int i = 0; i < 100; i++) {
        glm::vec3 new_pos = -1.0f * camera + glm::vec3(0, 1, 0) + dir * (float) i;

        int x = (int) new_pos.x;
        int y = (int) new_pos.y;
        int z = (int) new_pos.z;

        if(game_world->isBlockAtPos(x, y, z)) {
            u_lookingat->update3f(x, y, z);
            if(window->isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
                if(pressed) break;
                game_world->breakBlock(x, y, z);
                pressed = true;
            } else if(window->isMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
                if(pressed) break;

                new_pos = -1.0f * camera + glm::vec3(0, 1, 0) + dir * (float) (i - 1);

                x = (int) new_pos.x;
                y = (int) new_pos.y;
                z = (int) new_pos.z;

                game_world->placeBlock(x, y, z, 3);
                pressed = true;
            } else pressed = false;

            break;
        }
    }

    //cur_time += 0.001f;

    u_time->update1f(cur_time);
    u_camera->update3f(camera);
    u_rotation->update3f(rotation);
    
    game_world->render();

    shader->unbind();
}

game::Game::~Game() {
    delete u_time;
    delete u_camera;
    delete u_rotation;
    delete u_sampler;
    delete u_lookingat;

    delete shader;
    delete window;
    delete game_world;
}

void game::Game::run() {
    window->run();
}