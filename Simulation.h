#ifndef CONVOLVING_AUTOMATON_SIMULATION_H_
#define CONVOLVING_AUTOMATON_SIMULATION_H_

#include <random>
#include "FFT.h"
#include "FrameBufferRing.h"
#include "gl_includes.h"
#include "utils.h"
#include "Renderer.h"

namespace ca {

class Simulation {
  public:
    Simulation(const Size& world_size);

    /**
     * Initialize the simluation.
     * Requires a valid OpenGL context.
     */
    void Init();
  
    /**
     * Advance the state of the simulation by one timestep.
     */
    void Step();
    
    /**
     * Get a buffer to render the most recent state of the simulation.
	 * As soon as rendering is complete, the caller must pass the buffer
	 * back into UnlockRenderingBuffer()
     */
    FrameBuffer* LockRenderingBuffer();

    /**
     * Call this as soon as a rendering pass is complete to put the
     * buffer back in rotation.
     */
    void UnlockRenderingBuffer(FrameBuffer* rendering_buffer);

    /**
     * Returns a pointer to the buffer containing the fourier-transformed kernels.
     */
    FrameBuffer* kernels_fft() const;

  private:
	void InitKernels();
	void InitState();
	
    Size world_size_;
    FrameBuffer* kernels_fft_;
	float inner_sum_;
	float outer_sum_;

    std::default_random_engine generator_;
	FFT fft_;
	FrameBufferRing state_ring_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_SIMULATION_H_