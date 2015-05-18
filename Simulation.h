#ifndef CONVOLVING_AUTOMATON_SIMULATION_H_
#define CONVOLVING_AUTOMATON_SIMULATION_H_

#include "gl_includes.h"
#include "utils.h"
#include "Renderer.h"

namespace ca {

class Simulation {
 public:
  Simulation(const Size& world_size);
  void Init();
  
  // temp
  GLuint kernel_tex() { return kernel_tex_; }
 private:
  Size world_size_;
  GLuint kernel_tex_; // 2 kernels interleaved into 1 texture
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_SIMULATION_H_