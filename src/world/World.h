#pragma once

#include "Chunk.h"

namespace world {
    
    class World {
    private:
        std::vector<Chunk*> chunks;

    public:
        World();
        ~World();

        void render();

        inline bool isBlockAtPos(int x, int y, int z) {
            for(Chunk *c : chunks) if(c->isNotAir(x, y, z)) return true;
            return false;
        }

         inline void breakBlock(int x, int y, int z) { for(Chunk *c : chunks) if(c->isNotAir(x, y, z)) c->breakBlock(x & 0xF, y & 0xFF, z & 0xF); }
         inline void placeBlock(int x, int y, int z, int id) { for(Chunk *c : chunks) if(c->isInside(x, z) && !c->isNotAir(x, y, z)) c->placeBlock(x  & 0xF, y  & 0xFF, z  & 0xF, id); }
    };

}
