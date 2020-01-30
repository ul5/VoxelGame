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
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    //glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    window = glfwCreateWindow(960, 540, "Voxels", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    auto clock = std::chrono::high_resolution_clock();
    auto start = clock.now();

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        for(renderer r : renderers) r.func(r.user_ptr, this);

        glfwSetCursorPos(window, 0, 0);

        glfwSwapBuffers(window);
        ++fps;

        auto now = clock.now();
        if(now - start >= std::chrono::seconds(1)) {
            start = now;
            std::cout << "[INFO] " << fps << " FPS" << std::endl;
            fps = 0;
        }
    }
}