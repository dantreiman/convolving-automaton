#ifndef CONVOLVING_AUTOMATON_FFT_H_
#define CONVOLVING_AUTOMATON_FFT_H_
//
//  Performs parallel FFT using RGBA textures. 
//  Can do 2 DFTs at once in parallel.
//  Input and output expects 2 planes: R + Gi, B + Ai
//

#include <GLFW/glfw3.h>
#include <memory>
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
     * src must be RGBA, where R is the real 
     */
	void forward(GLuint src, GLuint dst);
	
	void inverse(GLuint src, GLuint dst);

  private:
    void GeneratePlanTextures();
    void GeneratePlanX();
    void GeneratePlanY();
	void LoadShader();
	
    Size size_;
    int log2x_;
    int log2y_;
    GLuint planx[MP2][2], plany[MP2][2];
	std::unique_ptr<Shader> shader_;
};

}

#endif  // CONVOLVING_AUTOMATON_FFT_H_
