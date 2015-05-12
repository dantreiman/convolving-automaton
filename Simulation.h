#ifndef CONVOLVING_AUTOMATON_SIMULATION_H_
#define CONVOLVING_AUTOMATON_SIMULATION_H_

#include <GLFW/glfw3.h>
#include "utils.h"
#include "Renderer.h"

namespace ca {

class Simulation {
 public:
  Simulation(const Size& world_size);
  void Init();
  
  // temp
  GLuint inner_kernel_tex() { return inner_kernel_tex_; }
 private:
  Size world_size_;
  GLuint inner_kernel_tex_;
  GLuint outer_kernel_tex_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_SIMULATION_H_