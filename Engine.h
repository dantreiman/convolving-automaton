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
  GLFWwindow* window_;
  GLFWmonitor* monitor_;
  Renderer renderer_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_ENGINE_H_