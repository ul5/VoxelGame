#include "BlockMesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

graphics::BlockMesh::BlockMesh(int xoff, int zoff) : x((float) xoff), z((float) zoff) {
    unsigned char *data = stbi_load("res/texture/test_atlas.png", &width, &height, &nrChannels, 0);
    if(data && nrChannels != 3 && nrChannels != 4) {
        std::cout << "[ERROR] How many channels does this picture have? It has %d..." << std::endl;
        return;
    }
    
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1, &vboID);
    glGenBuffers(1, &iboID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert_data), (void*) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vert_data), (void*) (sizeof(float) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vert_data), (void*) (sizeof(float) * 5));

    glBindVertexArray(0);
}

graphics::BlockMesh::~BlockMesh() {
    glDeleteTextures(1, &texture_id);
    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &iboID);
}

void graphics::BlockMesh::add_face(float x1, float y1, float z1, SIDE side, int tex_id) {
    float coord_x = tex_id % 64;
    float coord_y = (int)(tex_id / 64);

    unsigned int cur_id = (unsigned int) vertices.size();

    if(side == POSITIVE_X) {
        vertices.push_back({ x + x1 + 0.0f, y1 + 0.0f, z + z1 + 0.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 0.0f, y1 + 0.0f, z + z1 + 1.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 0.0f, y1 + 1.0f, z + z1 + 1.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 0.0f, y1 + 1.0f, z + z1 + 0.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
    } else if(side == NEGATIVE_X) {
        vertices.push_back({ x + x1 + 1.0f, y1 + 0.0f, z + z1 + 0.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 1.0f, z + z1 + 0.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 1.0f, z + z1 + 1.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 0.0f, z + z1 + 1.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
    } else if(side == POSITIVE_Y) {
        vertices.push_back({ x + x1 + 0.0f, y1 + 0.0f, z + z1 + 0.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 0.0f, z + z1 + 0.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 0.0f, z + z1 + 1.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 0.0f, y1 + 0.0f, z + z1 + 1.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
    } else if(side == NEGATIVE_Y) {
        vertices.push_back({ x + x1 + 0.0f, y1 + 1.0f, z + z1 + 0.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 0.0f, y1 + 1.0f, z + z1 + 1.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 1.0f, z + z1 + 1.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 1.0f, z + z1 + 0.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
    } else if(side == POSITIVE_Z) {
        vertices.push_back({ x + x1 + 0.0f, y1 + 0.0f, z + z1 + 0.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 0.0f, y1 + 1.0f, z + z1 + 0.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 1.0f, z + z1 + 0.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 0.0f, z + z1 + 0.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
    } else if(side == NEGATIVE_Z) {
        vertices.push_back({ x + x1 + 0.0f, y1 + 0.0f, z + z1 + 1.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 0.0f, z + z1 + 1.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 1.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 1.0f, y1 + 1.0f, z + z1 + 1.0f, (coord_x + 1.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
        vertices.push_back({ x + x1 + 0.0f, y1 + 1.0f, z + z1 + 1.0f, (coord_x + 0.0f) / 64.0f, (coord_y + 0.0f) / 64.0f, x + x1, y1, z + z1 });
    }

    indices.push_back(cur_id + 0);
    indices.push_back(cur_id + 1);
    indices.push_back(cur_id + 2);
    indices.push_back(cur_id + 2);
    indices.push_back(cur_id + 3);
    indices.push_back(cur_id + 0);
}

void graphics::BlockMesh::draw() {
    glBindVertexArray(vaoID);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert_data), (void*) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vert_data), (void*) (sizeof(float) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vert_data), (void*) (sizeof(float) * 5));

    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_data) * vertices.size(), &vertices[0], GL_STREAM_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STREAM_DRAW);

    glActiveTexture(GL_TEXTURE0);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*) nullptr);

    glBindVertexArray(0);
}

void graphics::BlockMesh::clear() {
    indices.clear();
    vertices.clear();
}