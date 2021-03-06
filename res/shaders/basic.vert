#version 330 core

#define PI 3.1415926535897932384622

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coords;
layout (location = 2) in vec3 blockpos;

uniform float time;
uniform vec3 camera;
uniform vec3 rotation;
uniform vec3 looking_at;

out vec3 pos;
out vec2 tex_coords;
out vec4 color_modifier;

mat4 rotx(float angle) {
    return transpose(mat4(1, 0, 0, 0, 0, cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle), 0, 0, 0, 0, 1));
}

mat4 roty(float angle) {
    return transpose(mat4(cos(angle), 0, -sin(angle), 0, 0, 1, 0, 0, sin(angle), 0, cos(angle), 0, 0, 0, 0, 1));
}

mat4 rotz(float angle) {
    return transpose(mat4(cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
}

mat4 transform(vec3 pos) {
    return transpose(mat4(1, 0, 0, pos.x, 0, 1, 0, pos.y, 0, 0, 1, pos.z, 0, 0, 0, 1));
}

mat4 perspective(float fovy, float near, float far) {
    float f = 1.0 / tan(fovy / 2.0);
    return transpose(mat4(
        f / 16.0 * 9.0, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (far+near)/(near-far), 2.0*far*near/(near - far),
        0, 0, -1, 0
    ));
}

void main() {
    gl_Position = perspective(PI / 4.0, 1, 100) * rotx(rotation.x) * roty(rotation.y) * transform(camera) * transform(vec3(0, -1, 0.5)) * roty(time * 100.0) * transform(vec3(0, 0, -0.5)) * vec4(position, 1);
    pos = position;

    tex_coords = texture_coords;

    if(blockpos == looking_at) {
        //color_modifier = vec4(1, 0, 1, 1);
        tex_coords.y += 1.0/64.0;
    } else color_modifier = vec4(0, 0, 0, 0);
}