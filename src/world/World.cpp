#include "World.h"

world::World::World() {
    for(int i = 0; i < 1; i++) {
        for(int j = 0; j < 1; j++) {
            chunks.push_back(new Chunk(i, j));
        }
    }
    chunks.push_back(new Chunk(0, 1));
}

world::World::~World() {
    for(Chunk *c : chunks) delete c;
}

void world::World::render() {
    for(Chunk *c : chunks) c->render();
}