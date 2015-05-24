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
     * Size must be a power of 2.
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
    void GeneratePlanX();
    void GeneratePlanY();
    void LoadShader();
    void Stage(int dim, int eb, int si, FrameBuffer* src, FrameBuffer* dst);
    
    Size size_;
    int log2x_;
    int log2y_;
    GLuint planx_[MP2][2], plany_[MP2][2];
    std::unique_ptr<Shader> shader_;
    GLuint vao_;
    struct {
        GLint dim_location;
        GLint tang_location;
        GLint tangsc_location;
        GLint state_tex_location;
        GLint plan_tex_location;
    } uniforms_;
};

}

#endif  // CONVOLVING_AUTOMATON_FFT_H_
