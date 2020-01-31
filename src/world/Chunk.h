#pragma once

#include "Block.h"
#include "../graphics/BlockMesh.h"

namespace world {

    class Chunk {
    private:
        world::Block **blocks = new world::Block*[16 * 16 * 256];
        graphics::BlockMesh *blockMesh = nullptr;

        void createMesh();

        int chunk_x, chunk_z;

    public:
        Chunk(int x, int y);
        ~Chunk();

        inline bool isInside(int x, int z) { return x >= chunk_x * 16 && x < (chunk_x + 1) * 16 && z >= chunk_z * 16 && z < (chunk_z + 1) * 16; }
        inline bool isNotAir(int x, int y, int z) { return isInside(x, z) && blocks[(x % 16) + (y % 256) * 16 + (z % 16) * 16 * 256]->blockid; }
        inline void breakBlock(int x, int y, int z) { blocks[(x % 16) + (y % 256) * 16 + (z % 16) * 16 * 256]->blockid = 0; createMesh(); }
        inline void placeBlock(int x, int y, int z, int bid) { blocks[(x % 16) + (y % 256) * 16 + (z % 16) * 16 * 256]->blockid = bid; createMesh(); }

        void render();
    };

}