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

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    vb = new graphics::VertexBuffer();

    window->addRenderFunc(game::game_render, this);
}

void game::Game::render(graphics::Window *window) {
    if(window->isKeyPressed(GLFW_KEY_ESCAPE)) window->closeWindow();

    glm::dvec2 mouse_pos = window->getMousePos();
    rotation.y -= mouse_pos.x / 1000.0;
    printf("Angle = %f\n", angle);

    float ws = 0.0f, ad = 0.0f;

    if(window->isKeyPressed(GLFW_KEY_W)) ws += 0.1f;
    if(window->isKeyPressed(GLFW_KEY_S)) ws -= 0.1f;
    if(window->isKeyPressed(GLFW_KEY_D)) ad -= 0.1f;
    if(window->isKeyPressed(GLFW_KEY_A)) ad += 0.1f;

    camera.z += cos(angle) * ws - sin(angle) * ad;
    camera.x += cos(angle) * ad + sin(angle) * ad;

    cur_time += 0.001f;

    shader->use();
    u_time->update1f(cur_time);
    u_camera->update3f(camera);
    u_rotation->update3f(rotation);

    vb->draw();
    shader->unbind();
}

game::Game::~Game() {
    delete u_time;
    delete u_camera;

    delete shader;
    delete vb;
    delete window;
}

void game::Game::run() {
    window->run();
}