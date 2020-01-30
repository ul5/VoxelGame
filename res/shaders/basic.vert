#version 330 core

#define PI 3.1415926535897932384622

layout (location = 0) in vec3 position;
uniform float time;
uniform vec3 camera;
uniform vec3 rotation;

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

mat4 transform(vec3 pos) {
    return transpose(mat4(1, 0, 0, pos.x, 0, 1, 0, pos.y, 0, 0, 1, pos.z, 0, 0, 0, 1));
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
    gl_Position = perspective(PI / 4.0, 1, 10) * roty(rotation.y) * transform(camera) * rotx(-PI / 4.0) * transform(vec3(0, -1, 0.5)) * roty(time * 100.0) * transform(vec3(0, 0, -0.5)) * vec4(position, 1);
    //gl_Position.w = 10;
    pos = position;
}