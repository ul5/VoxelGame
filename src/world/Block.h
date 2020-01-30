#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <stdint.h>

namespace world {

    typedef struct Block {
        uint32_t blockid;
        uint32_t x, y, z;

        Block(uint32_t bid, uint32_t x, uint32_t y, uint32_t z);
    } Block;

}