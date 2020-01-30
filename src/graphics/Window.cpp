#include "Window.h"

float cur_time = 0.0f;

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
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    //glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    window = glfwCreateWindow(960, 540, "Voxels", NULL, NULL);
    glfwMakeContextCurrent(window);
    //glfwSetWindowOpacity(window, 0.1f);
    

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

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    graphics::VertexBuffer *vb = new graphics::VertexBuffer();

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

        cur_time += 0.001f;
        shader->use();
        shader->uniform1f("time", cur_time);

        vb->draw();
        shader->unbind();

        glfwSwapBuffers(window);
    }

    delete shader;
}