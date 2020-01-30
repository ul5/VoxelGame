#include "VertexBuffer.h"

graphics::VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &iboID);

    float *points = new float[8 * 3];
    points[0] = -0.5f;
    points[1] = -0.5f;
    points[2] = 0;

    points[3] = 0.5f;
    points[4] = -0.5f;
    points[5] = 0;

    points[6] = 0.5f;
    points[7] = 0.5f;
    points[8] = 0;

    points[9] = -0.5f;
    points[10] = 0.5f;
    points[11] = 0;

    points[12] = -0.5f;
    points[13] = -0.5f;
    points[14] = 1;

    points[15] = 0.5f;
    points[16] = -0.5f;
    points[17] = 1;

    points[18] = 0.5f;
    points[19] = 0.5f;
    points[20] = 1;

    points[21] = -0.5f;
    points[22] = 0.5f;
    points[23] = 1;

    unsigned int * indicies = new unsigned int[6 * 6] { 
        0, 1, 2, 2, 3, 0,
        5, 4, 7, 7, 6, 5,
        1, 5, 6, 6, 2, 1,
        4, 0, 3, 3, 7, 4,
        0, 4, 5, 5, 1, 0,
        3, 2, 6, 6, 7, 3 
    };

    // bind();

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6 * 6, indicies, GL_STATIC_DRAW);
}

void graphics::VertexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, (void*) nullptr);
}

graphics::VertexBuffer::~VertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &iboID);
}