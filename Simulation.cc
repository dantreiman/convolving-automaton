#include "Simulation.h"

#include "Buffer.h"
#include "FrameBufferCache.h"
#include "Kernel.h"
#include "log.h"
#include "Vectors.h"

namespace ca {

Simulation::Simulation(const Size& world_size) : world_size_(world_size),
                                                 fft_(world_size) {
}

void Simulation::Init() {
    // InitKernels depends on FFT init being called first.
    fft_.Init();
    InitKernels();
    InitState();
}

void Simulation::Step() {
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    FrameBuffer * read = state_ring_.read_buffer();
    FrameBuffer * write = state_ring_.write_buffer();
    
    FrameBuffer * temp = cache->ReserveBuffer();
    
    cache->RecycleBuffer(temp);
    state_ring_.Rotate();
}

FrameBuffer* Simulation::LockRenderingBuffer() {
    return state_ring_.RemoveIdle();
}

void Simulation::UnlockRenderingBuffer(FrameBuffer* rendering_buffer) {
    state_ring_.Add(rendering_buffer);
}

FrameBuffer* Simulation::kernels_fft() const {
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
    // Compute the DFT of both kernels
    kernels_fft_ = fft_.Forward(kernel_buffer);
    cache->RecycleBuffer(kernel_buffer);
}


void Simulation::InitState() {
    // Set up state ring buffer
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    for (int i = 0; i < 3; i++) {
        FrameBuffer* buffer = cache->ReserveBuffer();
        state_ring_.Add(buffer);
    }
    // Configure initial state
    FrameBuffer * front_buffer = state_ring_.read_buffer();
    Buffer2D<Vec4<float>> state(world_size_);
    
    const float length = 32;
    const int iterations = 100;
    std::uniform_int_distribution<int> value_dist(0, 1);
    std::uniform_int_distribution<int> x_dist(0, world_size_.w);
    std::uniform_int_distribution<int> y_dist(0, world_size_.h);
    std::uniform_int_distribution<int> r_dist(length * .5, length * 1.5);
    for (int i = 0; i < iterations; i++) {
        float xo = x_dist(generator_);
        float yo = y_dist(generator_);
        float w = r_dist(generator_);
        float h = r_dist(generator_);
        float v = (float)value_dist(generator_);
        for (int x = xo; x < xo + w; x++) {
            for (int y = yo; y < yo + h; y++) {
                state.set(x % world_size_.w, y % world_size_.h, Vec4<float>(v, 0.0, 0.0, 0.0));
            }
        }
    }
    glBindTexture(GL_TEXTURE_2D, front_buffer->texture());    
    CHECK_GL_ERROR("glBindTexture");
    glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, world_size_.w, world_size_.h, GL_RGBA, GL_FLOAT, state.data());    
    CHECK_GL_ERROR("glTexSubImage2D");
}

}  // namespace ca