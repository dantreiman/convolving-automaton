#include "FFT.h"

#include <algorithm>
#include <cmath>
#include "FrameBufferCache.h"
#include "log.h"
#include "Quad.h"

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
    int x;
    int y;
    int wr;  // real weight
    int wi;  // imaginary weight
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
    for (int x_stage = 0; x_stage < log2x_; x_stage++) {
        Stage(0, x_stage, read, write);
		if (read == src) { read = temp2; } // Read from src on the 1st stage
        std::swap(read, write);
    }
    for (int y_stage = 0; y_stage < log2y_; y_stage++) {
        Stage(1, y_stage, read, write);
        std::swap(read, write);
    }
    cache->RecycleBuffer(write);
    return read;
}

FrameBuffer* FFT::Inverse(FrameBuffer* src) {
    const int si = 1; // -1 forward, 1 inverse
    // FrameBufferCache * cache = FrameBufferCache::sharedCache(size_);
    // FrameBuffer* temp1 = cache->ReserveBuffer();
    // FrameBuffer* temp2 = cache->ReserveBuffer();
    // FrameBuffer* read = src;
    // FrameBuffer* write = temp1;
    // for (int t = 1; t <= log2y_; t++) {
    //     Stage(2, t, si, read, write);
    //     if (read == src) { read = temp2; } // Read from src on the 1st stage
    //     std::swap(read, write);
    // }
    // for (int t = 0; t <= log2x_-1; t++) {
    //     Stage(1, t, si, read, write);
    //     std::swap(read, write);
    // }
    // cache->RecycleBuffer(read);
    // return write;
    return NULL;
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
    Butterfly butterfly[s * b];
    int n = 0;
    for(unsigned int i = 0; i < b; ++i)
    {
        int blocks = 1<<(b - 1 - i);
        int block_inputs = 1<<i;
        for(int j = 0; j < blocks; ++j)
            for(int k = 0; k < block_inputs; ++k)
        {
            int i1 = j*block_inputs*2 + k;
            int i2 = i1 + block_inputs;
            float j1, j2;
            if(i == 0)
            {
                j1 = static_cast<float>(bit_reverse(i1, s));
                j2 = static_cast<float>(bit_reverse(i2, s));
            }
            else
            {
                j1 = static_cast<float>(i1);
                j2 = static_cast<float>(i2);
            }
            i1 += n;
            i2 += n;
            butterfly[i1].x = j1;
            butterfly[i1].y = j2;
            butterfly[i2].x = j1;
            butterfly[i2].y = j2;

        // Compute weights
            double angle = 2.0*M_PI*k*blocks/static_cast<float>(s);
            float wr = static_cast<float>( cos(angle));
            float wi = static_cast<float>(-sin(angle));

            butterfly[i1].wr = wr;
            butterfly[i1].wi = wi;
            butterfly[i2].wr = -wr;
            butterfly[i2].wi = -wi;
        }
        n += s;
    }
    for (int stage = 0; stage < b; stage++) {
        glBindTexture (GL_TEXTURE_1D, plan_[stage]);
        CHECK_GL_ERROR("glBindTexture");
        glTexSubImage1D (GL_TEXTURE_1D, 0, 0, s, GL_RGBA, GL_FLOAT, &butterfly[stage * s]);
        CHECK_GL_ERROR("glTexSubImage1D");
    }
} 


void FFT::LoadShader() {
    Shader * shader = new Shader("fft2D_par");
    shader->Init(ShaderAttributes());
    shader_.reset(shader);
    uniforms_.dimension_location = shader->UniformLocation("dimension");
    uniforms_.inverse_location = shader->UniformLocation("inverse");
    uniforms_.state_tex_location = shader->UniformLocation("stateTex");
    uniforms_.plan_tex_location = shader->UniformLocation("planTex");
    // Create a VAO
    Quad quad = Quad(-1, -1, 2, 2);
    glGenVertexArrays(1, &vao_);
    CHECK_GL_ERROR("glGenVertexArrays");
    glBindVertexArray(vao_);
    CHECK_GL_ERROR("glBindVertexArray");
    GLuint posBufferName;
    glGenBuffers(1, &posBufferName);
    CHECK_GL_ERROR("glGenBuffers");
    glBindBuffer(GL_ARRAY_BUFFER, posBufferName);
    CHECK_GL_ERROR("glBindBuffer");
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), &quad.vertices[0], GL_STATIC_DRAW);
    CHECK_GL_ERROR("glBufferData");
    glEnableVertexAttribArray(POS_ATTRIB_LOCATION);
    CHECK_GL_ERROR("glEnableVertexAttribArray");
    glVertexAttribIPointer(POS_ATTRIB_LOCATION,
                           2,
                           GL_INT,
                           0,
                           BUFFER_OFFSET(0));
    CHECK_GL_ERROR("glVertexAttribIPointer");
}

void FFT::Stage(int dimension, int stage, FrameBuffer* src, FrameBuffer* dst) {
    // Renaming variables to preserve copy-pasted code
    const int NX = size_.w;
    const int NY = size_.h;
    const int BX = log2x_;
    const int BY = log2y_;
    
	dst->Bind();
    glViewport(0, 0, size_.w, size_.h);
    glUseProgram(shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    glUniform1i(uniforms_.inverse_location, 0);
    glUniform1i(uniforms_.dimension_location, dimension);
    CHECK_GL_ERROR("glUniform1i");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, src->texture());
    glUniform1i(uniforms_.state_tex_location, 0);

    glActiveTexture (GL_TEXTURE1);
    glBindTexture (GL_TEXTURE_1D, plan_[stage]);
    glUniform1i(uniforms_.plan_tex_location, 1);

    glBindVertexArray(vao_);
    CHECK_GL_ERROR("glBindVertexArray");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CHECK_GL_ERROR("glDrawArrays");
    
    glUseProgram(0);
}

}  // namespace ca