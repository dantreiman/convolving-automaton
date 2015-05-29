#include "Simulation.h"

#include "Buffer.h"
#include "FrameBufferCache.h"
#include "Kernel.h"
#include "log.h"
#include "Vectors.h"

namespace ca {

Simulation::Simulation(const Size& world_size) : world_size_(world_size),
                                                 kernels_(NULL),
                                                 fft_(world_size) {
}

void Simulation::Init() {
    // InitKernels depends on FFT init being called first.
    fft_.Init();
    InitKernels();
    InitState();
}

void Simulation::Step() {
    
}

FrameBuffer* Simulation::GetStateBuffer() const {
    // TODO: actually return the current unused state buffer
    return kernels_fft_;
}

void Simulation::InitKernels() {
    // Set up kernels
    Buffer2D<float> inner_kernel(world_size_);
    float inner_sum_ = CircularKernel(&inner_kernel, 7, 1);
    Buffer2D<float> outer_kernel(world_size_);
    float outer_sum_ = RingKernel(&outer_kernel, 7, 20, 1);
    
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
    CHECK_GL_ERROR("glTexSubImage2D");
    kernels_ = kernel_buffer;
    // Compute the DFT of both kernels
    kernels_fft_ = fft_.Forward(kernels_);
}


void Simulation::InitState() {
    // Set up state ring buffer
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    for (int i = 0; i < 3; i++) {
        FrameBuffer* buffer = cache->ReserveBuffer();
        state_ring_.Add(buffer);
    }
    // Configure initial state
    FrameBuffer * initialState = state_ring_.read_buffer();
    
    // glEnableClientState(GL_VERTEX_ARRAY);
    //     std::uniform_int_distribution<int> x_dist(0, rtt_size_.w);
    //     std::uniform_int_distribution<int> y_dist(0, rtt_size_.h);
    //     std::uniform_int_distribution<int> r_dist(length * .5, length * 1.5);
    //     
    //     // glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    //     for (int i = 0; i < iter; i++) {
    //         float x = x_dist(generator_);
    //         float y = y_dist(generator_);
    //         float w = r_dist(generator_);
    //         float h = r_dist(generator_);
    //  Quad quad(x, y, w, h);
    //  glVertexPointer(2, GL_INT, 0, quad.vertices);
    //  glDrawArrays(GL_TRIANGLE_STRIP, 0, 2);
    //     }
    // glDisableClientState(GL_VERTEX_ARRAY);
    
}


}  // namespace ca