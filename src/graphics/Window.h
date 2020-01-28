#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "VertexBuffer.h"

namespace graphics {

    class Window {
    private:
        GLFWwindow *window;

    public:
        Window();
        ~Window();
        void run();

    };

}