#pragma once

#include "Block.h"

namespace world {

    class Chunk {
    private:
        world::Block *blocks[16 * 16 * 256];

    public:
        Chunk();
        ~Chunk();

        void render();
    };

}