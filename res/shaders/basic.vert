#version 330 core

#define PI 3.1415926535897932384622

layout (location = 0) in vec3 position;
uniform float time;

out vec3 pos;

mat4 rotx(float angle) {
    return transpose(mat4(1, 0, 0, 0, 0, cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle), 0, 0, 0, 0, 1));
}

mat4 roty(float angle) {
    return transpose(mat4(cos(angle), 0, -sin(angle), 0, 0, 1, 0, 0, sin(angle), 0, cos(angle), 0, 0, 0, 0, 1));
}

mat4 rotz(float angle) {
    return transpose(mat4(cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
}

mat4 transform(float x, float y, float z) {
    return transpose(mat4(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1));
}

mat4 perspective(float fovy, float near, float far) {
    float f = 1.0 / tan(fovy / 2.0);
    return transpose(mat4(
        f / 16.0 * 9.0, 0, 0, 0,
        0,          f, 0, 0,
        0, 0, (far+near)/(near-far), 2*far*near/(near - far),
        0, 0, -1, 0
    ));
}

void main() {
    gl_Position = perspective(PI / 4.0, 1, 10) * rotx(PI / 4.0) * transform(0, -1, 1) * roty(time*100) * transform(0, 0, -0.5) * vec4(position, 1);
    gl_Position.w = time * 10;
    pos = position;
}