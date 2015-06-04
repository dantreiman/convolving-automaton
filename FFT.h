#ifndef CONVOLVING_AUTOMATON_FFT_H_
#define CONVOLVING_AUTOMATON_FFT_H_
//
//  Performs parallel FFT using RGBA textures. 
//  Can do 2 DFTs at once in parallel.
//  Input and output expects 2 planes: R + Gi, B + Ai
//

#include <memory>
#include "FrameBuffer.h"
#include "gl_includes.h"
#include "Shader.h"
#include "utils.h"

#define MP2 14  // The maximum power-of-two size allowed for buffers

namespace ca {

class FFT {
  public:
    /**
     * Size must be a power of 2 square.
     */
    FFT(const Size& size);
    void Init();

    /**
     * Fourier transform a texture.
     * Actually, performs 2 fourier transforms in parallel.
     * src must be RGBA, 1st plane (R + Gi)
     * 2nd plane (B + Ai)
     */
    FrameBuffer* Forward(FrameBuffer* src);
    
    FrameBuffer* Inverse(FrameBuffer* src);

  private:
    void GeneratePlanTextures();
    void GeneratePlan();
    void LoadShader();
    void Stage(int stage, int inverse, FrameBuffer* src, FrameBuffer* dst);
    
    Size size_;
    int log2x_;
    int log2y_;
    GLuint plan_[MP2];
    std::unique_ptr<Shader> forward_shader_;
    std::unique_ptr<Shader> inverse_shader_;
    struct {
        GLint dimension_location;
        GLint state_tex_location;
        GLint plan_tex_location;
    } uniforms_;
};

}

#endif  // CONVOLVING_AUTOMATON_FFT_H_
