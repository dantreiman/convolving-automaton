#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "log.h"

namespace {

// print shader info log to logfile
bool printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0) {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog (obj, infologLength, &charsWritten, infoLog);
        fprintf (LOGFILE, "%s\n", infoLog);
        free (infoLog);
    }
    return infologLength > 2;
}

bool printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0) {
        infoLog = (char *)malloc (infologLength);
        glGetProgramInfoLog (obj, infologLength, &charsWritten, infoLog);
        fprintf (LOGFILE, "%s\n", infoLog);
        free (infoLog);
    }
    return infologLength > 2;
}

}  // namespace

namespace ca {

Shader::Shader(const std::string& name) : name_(name) {
}

bool Shader::Init() {
    if (!Load()) {
        return false;
    }
    if (!Compile()) {
        return false;
    }
    return true;
}

const GLuint Shader::program() {
	return program_;
}

bool Shader::Load() {
    std::string vert_path = "shaders\\" + name_ + ".vert";
    std::ifstream vert_file(vert_path);
    std::stringstream vert_string;
    vert_string << vert_file.rdbuf();
    vert_src_ = vert_string.str();
    vertex_shader_ = glCreateShader (GL_VERTEX_SHADER);
    const char * vert_src_cstring = vert_src_.c_str();
    glShaderSource(vertex_shader_, 1, &vert_src_cstring, NULL);
    
    std::string frag_path = "shaders\\" + name_ + ".frag";
    std::ifstream frag_file(frag_path);
    std::stringstream frag_string;
    frag_string << frag_file.rdbuf();
    frag_src_ = frag_string.str();
    fragment_shader_ = glCreateShader (GL_FRAGMENT_SHADER);
    const char * frag_src_cstring = frag_src_.c_str();
    glShaderSource(fragment_shader_, 1, &frag_src_cstring, NULL);
    
    // TODO: error checking
    return true;
}

bool Shader::Compile() {
    bool result = true;
    glCompileShader(vertex_shader_);
    if (printShaderInfoLog(vertex_shader_)) {
        fprintf(LOGFILE, "error in vertex shader!\n\n");
        result &= false;
    }
    else {
        fprintf(LOGFILE, "vertex shader ok\n\n");
    }

    glCompileShader(fragment_shader_);
    if (printShaderInfoLog (fragment_shader_)) {
        fprintf(LOGFILE, "error in fragment shader!\n\n");
        result &= false;
    }
    else {
        fprintf(LOGFILE, "fragment shader ok\n\n");
    }

    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader_);
    glAttachShader(program_, fragment_shader_);

    glLinkProgram(program_);
    if (printProgramInfoLog(program_)) {
        fprintf(LOGFILE, "shader linking failed!\n\n");
        result &= false;
    }
    else {
        fprintf(LOGFILE, "shader program ok\n\n");
    }
    return result;
}

}  // namespace ca