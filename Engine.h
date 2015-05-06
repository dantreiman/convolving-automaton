#ifndef CONVOLVING_AUTOMATON_ENGINE_H_
#define CONVOLVING_AUTOMATON_ENGINE_H_

#include <GLFW/glfw3.h>
#include "utils.h"

namespace ca {

class Engine {
 public:
  Engine();
  virtual ~Engine();
  void Init();
  
  void RunLoop();

 private:
  Size render_size_;
  Size kernel_size_;
  GLFWwindow* window_;
  GLFWmonitor* monitor_;  
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_ENGINE_H_