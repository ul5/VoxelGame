#include "Chunk.h"

world::Chunk::Chunk() {
    for(int i = 0; i < 16 * 16 * 256; i++) {
        uint32_t x = i % 16;
        uint32_t y = (i / 16) % 256;
        uint32_t z = (i / 16 / 256) % 16;
        blocks[i] = new Block(y < 61 ? 1 : y < 64 ? 2 : 0, x, y, z);
    }
}

world::Chunk::~Chunk() {
    for(int i = 0; i < 16 * 16 * 256; i++) {
        delete blocks[i];
    }
}

void world::Chunk::render() {
    std::vector<glm::vec3> points;
    for(int i = 0; i < 16 * 16 * 256; i++) {
        if(!blocks[i]) continue;

        uint32_t x = i % 16;
        uint32_t y = (i / 16) % 256;
        uint32_t z = (i / 16 / 256) % 16;

        if(x == 0 || blocks[i - 1]->blockid) ; // left
        if(x == 15 || blocks[i + 1]->blockid) ; // right

        if(y == 0 || blocks[i - 16]); // bottom
        if(y == 255 || blocks[i + 16]); // top

        if(z == 0 || blocks[i - 16*256]) ; // front
        if(z == 15 || blocks[i + 16*256]) ; // back
    }
}