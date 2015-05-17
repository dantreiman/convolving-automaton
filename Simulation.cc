#include "Simulation.h"

#include "Buffer.h"
#include "FFT.h"
#include "Kernel.h"
#include "log.h"
#include "Vectors.h"

namespace ca {

Simulation::Simulation(const Size& world_size) : world_size_(world_size) {
}

void Simulation::Init() {
    // Temp: Generate textures
    glGenTextures (1, &kernel_tex_);
    CHECK_GL_ERROR("glGenTextures");
    Buffer2D<float> inner_kernel(world_size_);
    float inner_sum = CircularKernel(&inner_kernel, 7, 1);
    Buffer2D<float> outer_kernel(world_size_);
    float outer_sum = RingKernel(&outer_kernel, 7, 20, 1);
    
    Buffer2D<Vec4<float>> kernels(world_size_);
    
    for (int x = 0; x < world_size_.w; x++) {
        for (int y = 0; y < world_size_.h; y++) {
            kernels.set(x, y, Vec4<float>(inner_kernel.get(x, y), 0,
                                          outer_kernel.get(x, y), 0));
        }
    }
    
    glBindTexture(GL_TEXTURE_2D, kernel_tex_);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    CHECK_GL_ERROR("glBindTexture");
    // glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, world_size_.w, world_size_.h, GL_RED, GL_FLOAT, inner_kernel.data());
    //if (dims==2) glTexImage2D (GL_TEXTURE_2D, 0, GL_R32F, NX,NY, 0, GL_RED, GL_FLOAT, NULL);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 world_size_.w, world_size_.h,
                0, GL_RGBA, GL_FLOAT, kernels.data());
    CHECK_GL_ERROR("glTexImage2D");
    
    // Just to test, create an FFT
    FFT * fft = new FFT(world_size_);
    fft->Init();
    std::cout << "Initialized FFT" << std::endl;
}

}  // namespace ca