#ifndef CONVOLVING_AUTOMATON_SIMULATION_H_
#define CONVOLVING_AUTOMATON_SIMULATION_H_

#include "FFT.h"
#include "FrameBufferRing.h"
#include "gl_includes.h"
#include "utils.h"
#include "Renderer.h"

namespace ca {

class Simulation {
  public:
    Simulation(const Size& world_size);
    void Init();
  
    void Step();
    // temp
    FrameBuffer* GetStateBuffer() const;

  private:
	void InitKernels();
	void InitState();
	
    Size world_size_;
    FrameBuffer* kernels_;  // inner and outer kernel in (r,g) and (b,a) channels respectively
    FrameBuffer* kernels_fft_;
	float inner_sum_;
	float outer_sum_;

	FFT fft_;
	FrameBufferRing state_ring_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_SIMULATION_H_