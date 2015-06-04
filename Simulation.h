#ifndef CONVOLVING_AUTOMATON_SIMULATION_H_
#define CONVOLVING_AUTOMATON_SIMULATION_H_

#include <random>
#include "FFT.h"
#include "FrameBufferRing.h"
#include "gl_includes.h"
#include "utils.h"
#include "Renderer.h"
#include "Shader.h"

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
     * Run shader performance tests.
     */
    void TestPerformance();

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
    void LoadShaders();
    void InitKernels();
    void InitState();
    
    Size world_size_;
    std::unique_ptr<FrameBuffer> kernels_fft_;
    float inner_sum_;
    float outer_sum_;

    std::default_random_engine generator_;
    FFT fft_;
    FrameBufferRing state_ring_;
    
    std::unique_ptr<Shader> convolve_shader_;
    std::unique_ptr<Shader> sigmoid_shader_;
    struct {
        float inner_radius;
        float outer_radius;
        float border;
        float b1, b2;
        float d1, d2;
        float alphan;
        float alpham;
        float dt;
    } sl_parameters_;
    struct {
        // convolve_par.frag
        GLint scale_location;
        GLint kernels_fft_tex_location;
        GLint state_fft_tex_location;
        // sigmoid.frag
        GLint integral_tex_location;
        GLint state_tex_location;
    } uniforms_;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_SIMULATION_H_