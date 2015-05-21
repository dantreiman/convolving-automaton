#include "ShaderAttributes.h"

#include "gl_includes.h"
#include "log.h"

namespace ca {

ShaderAttributes::ShaderAttributes() {
}

ShaderAttributes::ShaderAttributes(GLuint location, const std::string& name) {
    attributes_.insert(AttributePair(location, name));
}

void ShaderAttributes::AddAttribute(GLuint location, const std::string& name) {
    attributes_.insert(AttributePair(location, name));
}

void ShaderAttributes::Bind(GLuint program) const {
    for (const AttributePair& attribute_pair : attributes_) {
        const GLuint attribute_index = attribute_pair.first;
        const std::string& attribute_name = attribute_pair.second;
        glBindAttribLocation(program, attribute_index, attribute_name.c_str());
        CHECK_GL_ERROR("glBindAttribLocation");
    }
}

}  // namespace ca