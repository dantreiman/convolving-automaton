#include "Simulation.h"

#include "Buffer.h"
#include "FFT.h"
#include "FrameBufferCache.h"
#include "Kernel.h"
#include "log.h"
#include "Vectors.h"

namespace ca {

Simulation::Simulation(const Size& world_size) : world_size_(world_size),
                                                 kernels_(NULL) {
}

void Simulation::Init() {
    Buffer2D<float> inner_kernel(world_size_);
    float inner_sum = CircularKernel(&inner_kernel, 7, 1);
    Buffer2D<float> outer_kernel(world_size_);
    float outer_sum = RingKernel(&outer_kernel, 7, 20, 1);
    
    Buffer2D<Vec4<float>> kernels(world_size_);
    Size half_size = Size(world_size_.w / 2, world_size_.h / 2);
    for (int x = 0; x < world_size_.w; x++) {
        for (int y = 0; y < world_size_.h; y++) {
            // Perform FFT shift
            const int shift_x = (x + half_size.w) % world_size_.w;
            const int shift_y = (y + half_size.h) % world_size_.h;
            // Interleave both kernels using r and b channels of the same image
            kernels.set(x, y, Vec4<float>(inner_kernel.get(shift_x, shift_y), 0,
                                          outer_kernel.get(shift_x, shift_y), 0));
        }
    }
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    FrameBuffer* kernel_buffer = cache->ReserveBuffer();
    glBindTexture(GL_TEXTURE_2D, kernel_buffer->texture());    
    CHECK_GL_ERROR("glBindTexture");
    glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, world_size_.w, world_size_.h, GL_RGBA, GL_FLOAT, kernels.data());    
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
    //              world_size_.w, world_size_.h,
    //             0, GL_RGBA, GL_FLOAT, kernels.data());
    CHECK_GL_ERROR("glTexSubImage2D");
    kernels_ = kernel_buffer;
    // Just to test, create an FFT
    FFT * fft = new FFT(world_size_);
    fft->Init();
    std::cout << "Initialized FFT" << std::endl;
    // Run an FFT
    kernels_fft_ = fft->Forward(kernels_);
	kernels_fft_inv_ = fft->Inverse(kernels_fft_);
}

FrameBuffer* Simulation::GetStateBuffer() const {
    // TODO: actually return the current unused state buffer
    return kernels_fft_inv_;
}

}  // namespace ca