#ifndef CONVOLVING_AUTOMATON_ENGINE_H_
#define CONVOLVING_AUTOMATON_ENGINE_H_

#include <GLFW/glfw3.h>
#include "utils.h"
#include "Renderer.h"

namespace ca {

class Engine {
 public:
  Engine();
  void Init();
  
  void RunLoop();

 private:
  Size render_size_;
  Size kernel_size_;
  GLFWwindow* window_;
  GLFWmonitor* monitor_;
  Renderer renderer;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_ENGINE_H_