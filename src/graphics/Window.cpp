#include "Window.h"

graphics::Window::Window() {
    if(glfwInit() != GLFW_TRUE) {
        const char *desc;
        glfwGetError(&desc);
        std::cout << "[ERROR] Could not initialize GLFW!" << desc << std::endl;
        return;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(960, 540, "Voxels", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    GLenum err;
    if((err = glewInit()) != GL_NO_ERROR) {
        std::cout << "[ERROR] Could not initialize GLEW: " << glewGetErrorString(err) << std::endl; 
        return;
    }
}

graphics::Window::~Window() {
    glfwDestroyWindow(window);
}

void graphics::Window::run() {
    glfwShowWindow(window);
    glfwMakeContextCurrent(window);

    graphics::Shader *shader = graphics::loadShaderFromFiles("res/shaders/basic.vert", "res/shaders/basic.frag");

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        shader->use();

        shader->unbind();

        glfwSwapBuffers(window);
    }

    delete shader;
}