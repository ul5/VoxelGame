#include "World.h"

world::World::World() {
    chunks.push_back(new Chunk());
}

world::World::~World() {
    for(Chunk *c : chunks) delete c;
}

void world::World::render() {
    for(Chunk *c : chunks) c->render();
}