#include "VertexBuffer.h"

#define NUM_POINTS 16
#define NUM_INDICIES 72

graphics::VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &iboID);

    float *points = new float[NUM_POINTS * 3] {
        -0.5f, -0.5f, 0,
        +0.5f, -0.5f, 0,
        +0.5f, +0.5f, 0,
        -0.5f, +0.5f, 0,
        -0.5f, -0.5f, 1,
        +0.5f, -0.5f, 1,
        +0.5f, +0.5f, 1,
        -0.5f, +0.5f, 1,

        -0.5f, -0.5f, 1,
        +0.5f, -0.5f, 1,
        +0.5f, +0.5f, 1,
        -0.5f, +0.5f, 1,
        -0.5f, -0.5f, 2,
        +0.5f, -0.5f, 2,
        +0.5f, +0.5f, 2,
        -0.5f, +0.5f, 2,
    };

    unsigned int * indicies = new unsigned int[NUM_INDICIES] { 
        0, 1, 2, 2, 3, 0,
        5, 4, 7, 7, 6, 5,
        1, 5, 6, 6, 2, 1,
        4, 0, 3, 3, 7, 4,
        0, 4, 5, 5, 1, 0,
        3, 2, 6, 6, 7, 3,

         8,  9, 10, 10, 11,  8,
        13, 12, 15, 15, 14, 13,
         9, 13, 14, 15, 10,  9,
        12,  8, 11, 11, 15, 12,
         8, 12, 13, 13,  9,  8,
        11, 10, 14, 14, 15, 11,
    };

    // bind();

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_POINTS * 3, points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NUM_INDICIES, indicies, GL_STATIC_DRAW);
}

void graphics::VertexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, NUM_INDICIES, GL_UNSIGNED_INT, (void*) nullptr);
}

graphics::VertexBuffer::~VertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &iboID);
}