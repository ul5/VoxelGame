#include <GL/glew.h>

#include "../util/ReadFile.h"

namespace graphics {

    class Shader {
    private:
        GLuint progID;

    public:
        Shader(const char *vert_src, const char *frag_src);

        inline void use() {glUseProgram(progID);}
        inline void unbind() {glUseProgram(0);}
    };

    Shader *loadShaderFromFiles(const char *vert_path, const char *frag_path);

}