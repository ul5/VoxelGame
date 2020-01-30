#pragma once
#include <GL/glew.h>

#include "../util/ReadFile.h"

namespace graphics {

    class ShaderUniform {
    private:
        GLuint location;

    public:
        ShaderUniform(GLuint loc) : location(loc) {}

        inline void update1f(float f) { glUniform1f(location, f); }
    };

    class Shader {
    private:
        GLuint progID;

    public:
        Shader(const char *vert_src, const char *frag_src);

        inline void use() {glUseProgram(progID);}
        inline void unbind() {glUseProgram(0);}

        inline ShaderUniform getUniform(const char * name) { return ShaderUniform(glGetUniformLocation(progID, name)); }
        inline void uniform1f(const char * name, float f) { glUniform1f(glGetUniformLocation(progID, name), f); }
    };

    Shader *loadShaderFromFiles(const char *vert_path, const char *frag_path);

}