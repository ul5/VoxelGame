#include "game/Game.h"

int main(void) {

    game::Game *game = new game::Game();
    game->run();
    delete game;

    return 0;
}