#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../util/ReadFile.h"

namespace graphics {

    class ShaderUniform {
    private:
        GLuint location;

    public:
        ShaderUniform(GLuint loc) : location(loc) {}

        inline void update1f(float f) { glUniform1f(location, f); }
        inline void update1i(int i) { glUniform1i(location, i); }

        inline void update3f(float v1, float v2, float v3) { glUniform3f(location, v1, v2, v3); }
        inline void update3i(int v1, int v2, int v3) { glUniform3i(location, v1, v2, v3); }
        inline void update3f(glm::vec3 f) { glUniform3fv(location, 1, glm::value_ptr(f)); }
    };

    class Shader {
    private:
        GLuint progID;

    public:
        Shader(const char *vert_src, const char *frag_src);

        inline void use() {glUseProgram(progID);}
        inline void unbind() {glUseProgram(0);}

        inline ShaderUniform *getUniform(const char * name) { return new ShaderUniform(glGetUniformLocation(progID, name)); }

        inline void uniform1f(const char * name, float f) { glUniform1f(glGetUniformLocation(progID, name), f); }
        inline void uniform3f(const char * name, float v1, float v2, float v3) { glUniform3f(glGetUniformLocation(progID, name), v1, v2, v3); }
        inline void uniform3f(const char * name, glm::vec3 f) { glUniform3fv(glGetUniformLocation(progID, name), 1, glm::value_ptr(f)); }
    };

    Shader *loadShaderFromFiles(const char *vert_path, const char *frag_path);

}