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

bool Shader::Init(const ShaderAttributes& attribute_bindings) {
    program_ = glCreateProgram();
    CHECK_GL_ERROR("glCreateProgram");
    // We have to bind shader attributes after program object created,
    // and before linking
    attribute_bindings.Bind(program_);
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

const GLint Shader::UniformLocation(const GLchar* name) {
    return glGetUniformLocation(program(), name);
}

bool Shader::Load() {
    std::string vert_path = "shaders/" + name_ + ".vert";
    std::ifstream vert_file(vert_path);
    vert_src_ = std::string((std::istreambuf_iterator<char>(vert_file)), std::istreambuf_iterator<char>());
    vertex_shader_ = glCreateShader (GL_VERTEX_SHADER);
    CHECK_GL_ERROR("glCreateShader");
    const char * vert_src_cstring = vert_src_.c_str();
    glShaderSource(vertex_shader_, 1, &vert_src_cstring, NULL);
    CHECK_GL_ERROR("glShaderSource");
    
    std::string frag_path = "shaders/" + name_ + ".frag";
    std::ifstream frag_file(frag_path);
    frag_src_ = std::string((std::istreambuf_iterator<char>(frag_file)), std::istreambuf_iterator<char>());
    fragment_shader_ = glCreateShader (GL_FRAGMENT_SHADER);
    CHECK_GL_ERROR("glCreateShader");
    const char * frag_src_cstring = frag_src_.c_str();
    glShaderSource(fragment_shader_, 1, &frag_src_cstring, NULL);
    CHECK_GL_ERROR("glShaderSource");
   
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
        //fprintf(LOGFILE, "vertex shader ok\n\n");
    }

    glCompileShader(fragment_shader_);
    if (printShaderInfoLog (fragment_shader_)) {
        fprintf(LOGFILE, "error in fragment shader!\n\n");
        result &= false;
    }
    else {
        //fprintf(LOGFILE, "fragment shader ok\n\n");
    }

    glAttachShader(program_, vertex_shader_);
    glAttachShader(program_, fragment_shader_);

    glLinkProgram(program_);
    if (printProgramInfoLog(program_)) {
        fprintf(LOGFILE, "shader linking failed!\n\n");
        fprintf(LOGFILE, "Vertex Shader:\n%s", vert_src_.c_str());
        fprintf(LOGFILE, "Fragment Shader:\n%s", frag_src_.c_str());
        result &= false;
    }
    else {
        //fprintf(LOGFILE, "shader program ok\n\n");        
    }
    return result;
}

}  // namespace ca