#ifndef CONVOLVING_AUTOMATON_FFT_H_
#define CONVOLVING_AUTOMATON_FFT_H_

#include <complex>
#include <GLFW/glfw3.h>
#include "Buffer.h"

#define MP2 20

namespace ca {

class FFT {
  public:
    /**
     * Size must be a power of 2.
     */
    FFT(const Size& size);

    void Init();

  private:
    void GeneratePlanTextures();
    void GeneratePlanX();
    void GeneratePlanY();
    
    Size size_;
    int log2x_;
    int log2y_;
    GLuint planx[MP2][2], plany[MP2][2];
};

}

#endif  // CONVOLVING_AUTOMATON_FFT_H_
