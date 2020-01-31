#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "Shader.h"

namespace graphics {

    typedef struct vert_data {
        float x, y, z;
        float t_x, t_y;
    } vert_data;

    enum SIDE {
        POSITIVE_X = 0,
        NEGATIVE_X,
        POSITIVE_Y,
        NEGATIVE_Y,
        POSITIVE_Z,
        NEGATIVE_Z
    };

    class BlockMesh {
    private:
        GLuint vaoID;
        GLuint vboID, iboID;
        GLuint texture_id;
        int width, height, nrChannels;

        std::vector<vert_data> vertices;
        std::vector<unsigned int> indices;
    public:
        BlockMesh();
        ~BlockMesh();

        void add_face(float x1, float y1, float z1, SIDE side, int tex_id);
        void draw();
        void clear();
    };

}