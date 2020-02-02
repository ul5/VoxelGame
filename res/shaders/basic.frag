#version 330 core

in vec3 pos;
in vec2 tex_coords;
in vec4 color_modifier;

out vec4 col;

uniform sampler2D tex;

void main() {
    col = texture(tex, tex_coords);

    if(color_modifier.w != 0) {
        col = color_modifier;
    }
}