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
    };

}
