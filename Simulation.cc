#include "Simulation.h"

#include "Buffer.h"
#include "FrameBufferCache.h"
#include "OpenGLTimer.h"
#include "Kernel.h"
#include "log.h"
#include "StopWatch.h"
#include "Vectors.h"
#include "VertexArray.h"

namespace ca {

Simulation::Simulation(const Size& world_size) : world_size_(world_size),
                                                 fft_(world_size),
                                                 current_scene_(0) {
    sl_parameters_ = SLParameters::GetPreset(0);
}

void Simulation::Init() {
    LoadShaders();
    // InitKernels depends on FFT init being called first.
    fft_.Init();
    InitKernels();
    InitState();
    scene_change_timer_.Start(20.0); // seconds
}

void Simulation::Step() {
    bool splat = false;
    if (scene_change_timer_.IsDone()) {
        current_scene_ = (current_scene_ + 1) % SLParameters::GetPresetCount();
        sl_parameters_ = SLParameters::GetPreset(current_scene_);
        UpdateParameters();
        scene_change_timer_.Start(20.0); // seconds
        splat = true;
    }
    
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    FrameBuffer* read = state_ring_.read_buffer();
    FrameBuffer* write = state_ring_.write_buffer();
    FrameBuffer* read_state = read;
    if (splat) {
        read_state = cache->ReserveBuffer();
        Splat(read_state, read);
    }
    // Step 1: take fourier transform of the state
    FrameBuffer* state_fft = fft_.Forward(read_state);
    // Step 2: convolution
    Convolve(write, kernels_fft_, state_fft);
    cache->RecycleBuffer(state_fft);
    // 'write' now contains the products of state with kernels
    // in the frequency domain.
    // Step 3: Parallel inverse fourier transform
    FrameBuffer * nm = fft_.Inverse(write);
    // Step 4: Compute derivative and apply
    Integrate(write, nm, read_state);
    cache->RecycleBuffer(nm);
    if (splat) {
        cache->RecycleBuffer(read_state);
    }
    glUseProgram(0);
    // Done, new state at t+dt is in write buffer.
    state_ring_.Rotate();
}

void Simulation::TestPerformance() {
    const int iterations = 5;
    StopWatch stop_watch("Simulation::Step");
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    for (int i = 0; i < iterations; i++) {
        OpenGLTimer timer("Step", iterations);
        FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
        FrameBuffer* read = state_ring_.read_buffer();
        FrameBuffer* write = state_ring_.write_buffer();
        // Step 1: take fourier transform of the state
        timer.Begin("FFT");
        FrameBuffer* state_fft = fft_.Forward(read);
        timer.End();
        // Step 2: convolution
        timer.Begin("Convolve");
        Convolve(write, kernels_fft_, state_fft);
        timer.End();
        cache->RecycleBuffer(state_fft);
        // 'write' now contains the products of state with kernels
        // in the frequency domain.
        // Step 3: Parallel inverse fourier transform
        timer.Begin("iFFT");
        FrameBuffer * nm = fft_.Inverse(write);
        timer.End();
        // Step 4: Compute derivative and apply
        timer.Begin("Integrate");
        Integrate(write, nm, read);
        timer.End();
        cache->RecycleBuffer(nm);
        glUseProgram(0);
        // Done, new state at t+dt is in write buffer.
        state_ring_.Rotate();
        timer.WaitForResults();
        std::cout << timer.Report() << std::endl;
    }
    glFinish();
    stop_watch.Mark("Completed");
    std::cout << stop_watch.Report();
    std::cout << static_cast<double>(iterations) / stop_watch.elapsed_time() << " Steps/sec" << std::endl;
}


void Simulation::TestFFTPerformance() {
    const int iterations = 60;
    StopWatch stop_watch("FFT::Forward");
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    OpenGLTimer timer("FFT Breakdown", iterations);
    for (int i = 0; i < iterations; i++) {
        FrameBuffer* read = state_ring_.read_buffer();
        timer.Begin("FFT");
        FrameBuffer* state_fft = fft_.Forward(read);
        timer.End();
        cache->RecycleBuffer(state_ring_.RemoveIdle());
        state_ring_.Add(state_fft);
        state_ring_.Rotate();
    }
    glFinish();
    stop_watch.Mark("fft.Forward");
    timer.WaitForResults();
    std::cout << timer.Report() << std::endl;
    std::cout << stop_watch.Report();
    std::cout << static_cast<double>(iterations) / stop_watch.elapsed_time() << " DFTs/sec" << std::endl;
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

void Simulation::LoadShaders() {
    Shader * convolve_shader = new Shader("minimal", "convolve_par");
    convolve_shader->Init(ShaderAttributes());
    convolve_shader_.reset(convolve_shader);
    uniforms_.scale_location = convolve_shader_->UniformLocation("scale");
    uniforms_.state_fft_tex_location = convolve_shader_->UniformLocation("stateFFT");
    uniforms_.kernels_fft_tex_location = convolve_shader_->UniformLocation("kernelsFFT");

    Shader * sigmoid_shader = new Shader("minimal", "sigmoid");
    sigmoid_shader->Init(ShaderAttributes());
    sigmoid_shader_.reset(sigmoid_shader);
    GLint integral_tex_location;
    GLint state_tex_location;
    uniforms_.integral_tex_location = sigmoid_shader_->UniformLocation("integralTexture");
    uniforms_.state_tex_location = sigmoid_shader_->UniformLocation("stateTexture");
    UpdateParameters();

    Shader * mix_shader = new Shader("minimal", "mix");
    mix_shader->Init(ShaderAttributes());
    mix_shader_.reset(mix_shader);
    uniforms_.mix_a_location = mix_shader->UniformLocation("mixA");
    uniforms_.mix_b_location = mix_shader->UniformLocation("mixB");
}

void Simulation::InitKernels() {
    // Set up kernels
    Buffer2D<float> inner_kernel(world_size_);
    inner_sum_ = CircularKernel(&inner_kernel,
                                sl_parameters_.inner_radius,
                                sl_parameters_.border);
    Buffer2D<float> outer_kernel(world_size_);
    outer_sum_ = RingKernel(&outer_kernel,
                             sl_parameters_.inner_radius,
                             sl_parameters_.outer_radius,
                            sl_parameters_.border);
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
    // recycle old kernels is we already had some generated
    if (kernels_fft_) {
        cache->RecycleBuffer(kernels_fft_);
    }
    FrameBuffer* kernels_buffer = cache->ReserveBuffer();
    glBindTexture(GL_TEXTURE_2D, kernels_buffer->texture());    
    CHECK_GL_ERROR("glBindTexture");
    glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, world_size_.w, world_size_.h, GL_RGBA, GL_FLOAT, kernels.data());    
    CHECK_GL_ERROR("glTexSubImage2D");
    // Compute the DFT of both kernels
    kernels_fft_ = fft_.Forward(kernels_buffer);
    cache->RecycleBuffer(kernels_buffer);
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
    
    const float length = 40;
    const int iterations = 200;
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

void Simulation::Convolve(FrameBuffer* output, FrameBuffer* kernels_fft, FrameBuffer* state_fft) {
    output->BindFrameBuffer();
    glViewport(0, 0, world_size_.w, world_size_.h);
    glUseProgram(convolve_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    // TODO: Premultiply kernels by scale factor
    glUniform2f(uniforms_.scale_location, 1./inner_sum_, 1./outer_sum_);
    CHECK_GL_ERROR("glUniform2f");
    glActiveTexture (GL_TEXTURE1);
    glBindTexture (GL_TEXTURE_2D, kernels_fft->texture());
    glUniform1i(uniforms_.kernels_fft_tex_location, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, state_fft->texture());
    glUniform1i(uniforms_.state_fft_tex_location, 0);
    VertexArray::Default()->Bind();
    VertexArray::Default()->Draw();
}

void Simulation::Integrate(FrameBuffer* output, FrameBuffer* nm, FrameBuffer* state) {
    output->BindFrameBuffer();
    glViewport(0, 0, world_size_.w, world_size_.h);
    glUseProgram(sigmoid_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    glActiveTexture (GL_TEXTURE1);
    glBindTexture (GL_TEXTURE_2D, state->texture());
    glUniform1i(uniforms_.state_tex_location, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, nm->texture());
    glUniform1i(uniforms_.integral_tex_location, 0);
    VertexArray::Default()->Bind();
    VertexArray::Default()->Draw();
}

void Simulation::UpdateParameters() {
    // TODO: make these parameters continuously variable
    glUseProgram(sigmoid_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    glUniform1f(sigmoid_shader_->UniformLocation("b1"), sl_parameters_.b1);
    glUniform1f(sigmoid_shader_->UniformLocation("b2"), sl_parameters_.b2);
    glUniform1f(sigmoid_shader_->UniformLocation("d1"), sl_parameters_.d1);
    glUniform1f(sigmoid_shader_->UniformLocation("d2"), sl_parameters_.d2);
    glUniform1f(sigmoid_shader_->UniformLocation("sn"), sl_parameters_.alphan);
    glUniform1f(sigmoid_shader_->UniformLocation("sm"), sl_parameters_.alpham);
    glUniform1f(sigmoid_shader_->UniformLocation("dt"), sl_parameters_.dt);
    CHECK_GL_ERROR("glUniform1f");
    glUseProgram(0);
}

void Simulation::Splat(FrameBuffer* output, FrameBuffer* state) {
    FrameBufferCache* cache = FrameBufferCache::sharedCache(world_size_);
    FrameBuffer * mixB = cache->ReserveBuffer();
    // make random features
    Buffer2D<Vec4<float>> mix(world_size_);
    const float length = 40;
    const int iterations = 200;
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
                mix.set(x % world_size_.w, y % world_size_.h, Vec4<float>(v, 0.0, 0.0, 0.0));
            }
        }
    }
    glBindTexture(GL_TEXTURE_2D, mixB->texture());
    CHECK_GL_ERROR("glBindTexture");
    glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, world_size_.w, world_size_.h, GL_RGBA, GL_FLOAT, mix.data());    
    CHECK_GL_ERROR("glTexSubImage2D");
    
    output->BindFrameBuffer();
    glViewport(0, 0, world_size_.w, world_size_.h);
    glUseProgram(mix_shader_->program());
    CHECK_GL_ERROR("glUseProgram");

    glActiveTexture (GL_TEXTURE1);
    glBindTexture (GL_TEXTURE_2D, mixB->texture());
    glUniform1i(uniforms_.mix_b_location, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, state->texture());
    glUniform1i(uniforms_.mix_a_location, 0);
    VertexArray::Default()->Bind();
    VertexArray::Default()->Draw();
    cache->RecycleBuffer(mixB);
}


}  // namespace ca