#include "Shader.h"

#include <string>
#include <iostream>
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

Shader::Shader(const std::string& vert_src, const std::string& frag_src) :
    vert_src_(vert_src), frag_src_(frag_src) {}

bool Shader::Init(const ShaderAttributes& attribute_bindings) {
    program_ = glCreateProgram();
    CHECK_GL_ERROR("glCreateProgram");
    // We have to bind shader attributes after program object created,
    // and before linking
    attribute_bindings.Bind(program_);
    
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