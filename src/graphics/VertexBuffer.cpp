#include "VertexBuffer.h"

graphics::VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &iboID);

    float *points = new float[4 * 3];
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

    unsigned int * indicies = new unsigned int[6] { 0, 1, 2, 2, 3, 0 };

    // bind();

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 3, points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indicies, GL_STATIC_DRAW);
}

void graphics::VertexBuffer::draw() {
    GLenum err = glGetError();
    if(err != GL_NO_ERROR) {
        std::cout << "[ERROR already happened]" << err << std::endl;
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) nullptr);
    if(glGetError() != GL_NO_ERROR) {
        std::cout << "[ERROR] drawing" << std::endl;
    }
}

graphics::VertexBuffer::~VertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &iboID);
}