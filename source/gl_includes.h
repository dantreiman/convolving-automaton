#ifndef CONVOLVING_AUTOMATON_GL_INCLUDES_H_
#define CONVOLVING_AUTOMATON_GL_INCLUDES_H_

//#define GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GLCOREARB  // On OSX, include gl3.h
//#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace ca {

// Common vertex shader attribute locations
// Defined in shaders
enum {
    // layout(location = 0) in ivec2 position;
    POS_ATTRIB_LOCATION = 0,
    TEX_ATTRIB_LOCATION = 1
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_GL_INCLUDES_H_
