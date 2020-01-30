#include "Game.h"

game::Game::Game() {
    window = new graphics::Window(); // Initialize all GL stuffs
}

game::Game::~Game() {
    delete window;
}

void game::Game::run() {
    window->run();
}