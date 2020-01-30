#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "../math/Vector.h"

namespace graphics {

    class VertexBuffer {
    private:
        std::vector<math::vec3> points;
        GLuint vboID, iboID;

    public:
        VertexBuffer();
        ~VertexBuffer();

        void draw();

        inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, vboID); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID); }
    };

}