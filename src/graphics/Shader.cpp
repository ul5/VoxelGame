#include "Shader.h"

graphics::Shader::Shader(const char *vert_src, const char *frag_src) {
    GLuint vertShader, fragShader;
    GLint compile_status;

    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertShader, 1, &vert_src, NULL);
    glShaderSource(fragShader, 1, &frag_src, NULL);

    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE) {
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &compile_status);
        char *log = (char*) malloc(compile_status + 1);
        glGetShaderInfoLog(vertShader, compile_status, NULL, log);
        std::cout << "[ERROR] Could not compile Vertex Shader: " << std::endl << log << std::endl;
        std::cout << vert_src;
        free(log);
    }

    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE) {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &compile_status);
        char *log = (char*) malloc(compile_status + 1);
        glGetShaderInfoLog(fragShader, compile_status, NULL, log);
        std::cout << "[ERROR] Could not compile Fragment Shader: " << std::endl << log << std::endl;
        std::cout << frag_src;
        free(log);
    }

    progID = glCreateProgram();
    glAttachShader(progID, vertShader);
    glAttachShader(progID, fragShader);
    glLinkProgram(progID);

    glGetProgramiv(progID, GL_LINK_STATUS, &compile_status);
    if(compile_status != GL_TRUE) {
        glGetProgramiv(progID,  GL_INFO_LOG_LENGTH, &compile_status);
        char *log = (char*) malloc(compile_status + 1);
        glGetProgramInfoLog(progID, compile_status, NULL, log);
        std::cout << "[ERROR] Could not Link program..." << std::endl << log << std::endl;
        free(log);
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

graphics::Shader *graphics::loadShaderFromFiles(const char *vert_path, const char *frag_path) {
    util::filedata f1 = util::readFile(vert_path);
    util::filedata f2 = util::readFile(frag_path);
    graphics::Shader *s = new graphics::Shader(f1.file_data, f2.file_data);

    free(f1.file_data);
    free(f2.file_data);

    return s;
}