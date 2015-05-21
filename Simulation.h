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
    FrameBuffer* GetStateBuffer() const;
  private:
    Size world_size_;
    FrameBuffer* kernels_;  // inner and outer kernel in (r,g) and (b,a) channels respectively
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_SIMULATION_H_