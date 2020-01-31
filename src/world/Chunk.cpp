#include "Chunk.h"

world::Chunk::Chunk() {
    for(int i = 0; i < 16 * 16 * 256; i++) {
        uint32_t x = i % 16;
        uint32_t y = (i / 16) % 256;
        uint32_t z = (i / 16 / 256) % 16;
        blocks[i] = new Block(y < 61 ? 1 : y < 64 ? 2 : 0, x, y, z);
    }

    blockMesh = new graphics::BlockMesh();
    createMesh();
}

world::Chunk::~Chunk() {
    for(int i = 0; i < 16 * 16 * 256; i++) {
        delete blocks[i];
    }

    delete blockMesh;
}

void world::Chunk::createMesh() {
    std::vector<glm::vec3> points;
    for(int i = 0; i < 16 * 16 * 256; i++) {
        if(!blocks[i] || !blocks[i]->blockid) continue;

        uint32_t x = i % 16;
        uint32_t y = (i / 16) % 256;
        uint32_t z = (i / 16 / 256) % 16;

        if(x == 0 || !blocks[i - 1]->blockid) blockMesh->add_face(x, y, z, graphics::POSITIVE_X, blocks[i]->blockid); // left
        if(x == 15 || !blocks[i + 1]->blockid) blockMesh->add_face(x, y, z, graphics::NEGATIVE_X, blocks[i]->blockid); // right

        if(y == 0 || !blocks[i - 16]->blockid) blockMesh->add_face(x, y, z, graphics::POSITIVE_Y, blocks[i]->blockid); // bottom
        if(y == 255 || !blocks[i + 16]->blockid) blockMesh->add_face(x, y, z, graphics::NEGATIVE_Y, blocks[i]->blockid); // top

        if(z == 0 || !blocks[i - 16*256]->blockid) blockMesh->add_face(x, y, z, graphics::POSITIVE_Z, blocks[i]->blockid); // front
        if(z == 15 || !blocks[i + 16*256]->blockid) blockMesh->add_face(x, y, z, graphics::NEGATIVE_Z, blocks[i]->blockid); // back
    }
}

void world::Chunk::render() {
    blockMesh->draw();
}