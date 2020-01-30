#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

#include "Shader.h"
#include "VertexBuffer.h"

namespace graphics {

    class Window;

    typedef void (*render_func)(void *user_ptr, Window *window);
    
    typedef struct renderer {
        render_func func;
        void *user_ptr;
    } renderer;

    class Window {
    private:
        GLFWwindow *window;
        std::vector<renderer> renderers;
        uint32_t fps = 0;

    public:
        Window();
        ~Window();

        inline void addRenderFunc(render_func f) { renderers.push_back({ f, nullptr }); }
        inline void addRenderFunc(render_func f, void * userdata) { renderers.push_back({ f, userdata }); }

        inline bool isKeyPressed(int key) { return glfwGetKey(window, key) == GLFW_PRESS; }
        inline void closeWindow() { glfwSetWindowShouldClose(window, true); }
        inline glm::dvec2 getMousePos() { glm::dvec2 pos; glfwGetCursorPos(window, &pos.x, &pos.y); return pos; }

        void run();

    };

}