#include "FFT.h"

#include <algorithm>
#include <cmath>
#include "FrameBufferCache.h"
#include "log.h"
#include "VertexArray.h"

namespace {

int bit_reverse(int i, int N) {
    int j = 0;
    while((N = N>>1)) {
        j = (j<<1) | (i&1);
        i = i>>1;
    }
    return j;
}

int log2int(unsigned int v) {
    static const unsigned int b[] = {0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 
                                     0xFF00FF00, 0xFFFF0000};
    unsigned int r = (v & b[0]) != 0;
    for (int i = 4; i > 0; i--) {
      r |= ((v & b[i]) != 0) << i;
    }
    return r;
}

struct Butterfly {
    float x;
    float y;
    float wr;  // real weight
    float wi;  // imaginary weight
};

}  // namespace

namespace ca {

FFT::FFT(const Size& size) : size_(size) {
    log2x_ = log2int(size.w);
    log2y_ = log2int(size.h);
}

void FFT::Init() {
    GeneratePlanTextures();
    GeneratePlan();
    LoadShader();
}

FrameBuffer* FFT::Forward(FrameBuffer* src) {
    FrameBufferCache * cache = FrameBufferCache::sharedCache(size_);
    FrameBuffer* temp1 = cache->ReserveBuffer();
    FrameBuffer* temp2 = cache->ReserveBuffer();
    FrameBuffer* read = src;
    FrameBuffer* write = temp1;
    glUseProgram(forward_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    for (int x_stage = 0; x_stage < log2x_; x_stage++) {
        Stage(0, x_stage, 0, read, write);
        if (read == src) { read = temp2; } // Read from src on the 1st stage
        std::swap(read, write);
    }
    for (int y_stage = 0; y_stage < log2y_; y_stage++) {
        Stage(1, y_stage, 0, read, write);
        std::swap(read, write);
    }
    cache->RecycleBuffer(write);
    glUseProgram(0);
    return read;
}

FrameBuffer* FFT::Inverse(FrameBuffer* src) {
    FrameBufferCache * cache = FrameBufferCache::sharedCache(size_);
    FrameBuffer* temp1 = cache->ReserveBuffer();
    FrameBuffer* temp2 = cache->ReserveBuffer();
    FrameBuffer* read = src;
    FrameBuffer* write = temp1;
    glUseProgram(inverse_shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    for (int x_stage = 0; x_stage < log2x_; x_stage++) {
        Stage(0, x_stage, 1, read, write);
        if (read == src) { read = temp2; } // Read from src on the 1st stage
        std::swap(read, write);
    }
    for (int y_stage = 0; y_stage < log2y_; y_stage++) {
        Stage(1, y_stage, 1, read, write);
        std::swap(read, write);
    }
    cache->RecycleBuffer(write);
    glUseProgram(0);
    return read;
}

void FFT::GeneratePlanTextures() {
    const int n = size_.w;
    const int b = log2x_;
    glGenTextures (b, &plan_[0]);
    CHECK_GL_ERROR("glGenTextures");
    for (int stage = 0; stage < b; stage++) {
        glBindTexture (GL_TEXTURE_1D, plan_[stage]);
        CHECK_GL_ERROR("glBindTexture");
        glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexImage1D (GL_TEXTURE_1D, 0, GL_RGBA, n, 0, GL_RGBA, GL_FLOAT, NULL);
        CHECK_GL_ERROR("glTexImage1D");
    }
}

void FFT::GeneratePlan() {
    const int s = size_.w;
    const int b = log2x_;
    // Butterflys butterflys: I was really high when I wrote this.
    Butterfly butterfly[s * b];
    int n = 0;
    for (int i = 0; i < b; ++i) {
        int blocks = 1<<(b - 1 - i);
        int block_inputs = 1<<i;
        for (int j = 0; j < blocks; ++j) {
            for (int k = 0; k < block_inputs; ++k) {
                int i1 = j*block_inputs*2 + k;
                int i2 = i1 + block_inputs;
                float j1, j2;
                if (i == 0) {
                    j1 = static_cast<float>(bit_reverse(i1, s));
                    j2 = static_cast<float>(bit_reverse(i2, s));
                }
                else {
                    j1 = static_cast<float>(i1);
                    j2 = static_cast<float>(i2);
                }
                i1 += n;
                i2 += n;
                // normalize scramblers for use as texture coordinates
                butterfly[i1].x = j1 / float(s);
                butterfly[i1].y = j2 / float(s);
                butterfly[i2].x = j1 / float(s);
                butterfly[i2].y = j2 / float(s);

            // Compute weights
                double angle = 2.0*M_PI*k*blocks/static_cast<float>(s);
                float wr = static_cast<float>( cos(angle));
                float wi = static_cast<float>(-sin(angle));

                butterfly[i1].wr = wr;
                butterfly[i1].wi = wi;
                butterfly[i2].wr = -wr;
                butterfly[i2].wi = -wi;
            }
        }
        n += s;
    }
    for (int stage = 0; stage < b; stage++) {
        // Write plan to stdout for debugging
        // if (stage == 1) {
        //  for (int i = 0; i < s; i++) {
        //      Butterfly& b = butterfly[i];
        //      std::cout << "( " << b.x << ", " << b.y << ", " << b.wr << ", " << b.wi << " )" << std::endl;
        //  }
        // }
        glBindTexture (GL_TEXTURE_1D, plan_[stage]);
        CHECK_GL_ERROR("glBindTexture");
        glTexSubImage1D (GL_TEXTURE_1D, 0, 0, s, GL_RGBA, GL_FLOAT, &butterfly[stage * s]);
        CHECK_GL_ERROR("glTexSubImage1D");
    }
} 

void FFT::LoadShader() {
    Shader * forward_shader = new Shader("minimal", "fft2D_forward_par");
    forward_shader->Init(ShaderAttributes());
    forward_shader_.reset(forward_shader);
    Shader * inverse_shader = new Shader("minimal", "fft2D_inverse_par");
    inverse_shader->Init(ShaderAttributes());
    inverse_shader_.reset(inverse_shader);
    // Forward and inverse shaders share the same uniform locations here
    uniforms_.dimension_location = forward_shader->UniformLocation("dimension");
    uniforms_.state_tex_location = forward_shader->UniformLocation("stateTex");
    uniforms_.plan_tex_location = forward_shader->UniformLocation("planTex");
}

void FFT::Stage(int dimension, int stage, int inverse, FrameBuffer* src, FrameBuffer* dst) {
    dst->BindFrameBuffer();
    glViewport(0, 0, size_.w, size_.h);
    glUniform1i(uniforms_.dimension_location, dimension);
    CHECK_GL_ERROR("glUniform1i");

    glActiveTexture (GL_TEXTURE1);
    glBindTexture (GL_TEXTURE_1D, plan_[stage]);
    glUniform1i(uniforms_.plan_tex_location, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, src->texture());
    glUniform1i(uniforms_.state_tex_location, 0);
     
    VertexArray::Default()->Bind();
    VertexArray::Default()->Draw();    
}

}  // namespace ca