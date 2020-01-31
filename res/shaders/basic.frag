#version 330 core

in vec3 pos;
in vec2 tex_coords;

out vec4 col;

uniform sampler2D tex;

void main() {
    col = texture(tex, tex_coords);
}