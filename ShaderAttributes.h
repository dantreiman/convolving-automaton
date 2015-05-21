#ifndef CONVOLVING_AUTOMATON_SHADER_ATTRIBUTES_H_
#define CONVOLVING_AUTOMATON_SHADER_ATTRIBUTES_H_

#include <map>
#include <string>
#include "gl_includes.h"

namespace ca {

class ShaderAttributes {
    typedef std::pair<GLuint, std::string> AttributePair;
  public:
    ShaderAttributes();
    ShaderAttributes(GLuint location, const std::string& name);

    void AddAttribute(GLuint location, const std::string& name);

    void Bind(GLuint program) const;

  private:
    std::map<GLuint, std::string> attributes_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_SHADER_ATTRIBUTES_H_
