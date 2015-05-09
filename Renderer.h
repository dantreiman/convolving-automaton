#ifndef CONVOLVING_AUTOMATON_RENDERER_H_
#define CONVOLVING_AUTOMATON_RENDERER_H_

#include <GLFW/glfw3.h>

namespace ca {

class Renderer {
 public:
  Renderer();
  
  void DrawScene(GLFWwindow* window, double t);

};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_RENDERER_H_