#pragma once

#include "Block.h"
#include "../graphics/BlockMesh.h"

namespace world {

    class Chunk {
    private:
        world::Block *blocks[16 * 16 * 256];
        graphics::BlockMesh *blockMesh = nullptr;

        void createMesh();

    public:
        Chunk();
        ~Chunk();

        void render();
    };

}