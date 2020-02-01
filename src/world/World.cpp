#include "World.h"

world::World::World() {
    for(int i = -2; i < 3; i++) {
        for(int j = -2; j < 3; j++) {
            chunks.push_back(new Chunk(i, j));
        }
    }
}

world::World::~World() {
    for(Chunk *c : chunks) delete c;
}

void world::World::render() {
    for(Chunk *c : chunks) c->render();
}