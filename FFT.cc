#include "FFT.h"

#include <algorithm>
#include <cmath>
#include "FrameBufferCache.h"
#include "log.h"
#include "Quad.h"

namespace {

int bitreverse (int x, int b) {
    int c = 0;
    for (int t = 0; t < b; t++) {
        c = (c<<1) | ((x>>t) & 1);
    }
    return c;
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

}  // namespace

namespace ca {

FFT::FFT(const Size& size) : size_(size) {
    log2x_ = log2int(size.w);
    log2y_ = log2int(size.h);
}

void FFT::Init() {
    GeneratePlanTextures();
    GeneratePlanX();
    GeneratePlanY();
    LoadShader();
}

FrameBuffer* FFT::Forward(FrameBuffer* src) {
    const int si = -1; // -1 forward, 1 inverse
    FrameBufferCache * cache = FrameBufferCache::sharedCache(size_);
    FrameBuffer* temp1 = cache->ReserveBuffer();
    FrameBuffer* temp2 = cache->ReserveBuffer();
    FrameBuffer* read = src;
    FrameBuffer* write = temp1;
    for (int t = 1; t <= log2x_; t++) {
        Stage(1, t, si, read, write);
        if (read == src) { read = temp2; } // Read from src on the 1st stage
        std::swap(read, write);
    }
    for (int t = 1; t <= log2y_; t++) {
        Stage(2, t, si, read, write);
        std::swap(read, write);
    }
    cache->RecycleBuffer(write);
    return read;
}

FrameBuffer* FFT::Inverse(FrameBuffer* src) {
    const int si = 1; // -1 forward, 1 inverse
    FrameBufferCache * cache = FrameBufferCache::sharedCache(size_);
    FrameBuffer* temp1 = cache->ReserveBuffer();
    FrameBuffer* temp2 = cache->ReserveBuffer();
    FrameBuffer* read = src;
    FrameBuffer* write = temp1;
    for (int t = 1; t <= log2y_; t++) {
        Stage(2, t, si, read, write);
        if (read == src) { read = temp2; } // Read from src on the 1st stage
        std::swap(read, write);
    }
    for (int t = 0; t <= log2x_-1; t++) {
        Stage(1, t, si, read, write);
        std::swap(read, write);
    }
    cache->RecycleBuffer(read);
    return write;
}

void FFT::GeneratePlanTextures() {
    const int NX = size_.w,
              NY = size_.h,
              BX = log2x_,
              BY = log2y_;
                
    glGenTextures ((BX-1+2)*2, &planx_[0][0]);
    CHECK_GL_ERROR("glGenTextures");
    for (int s = 0; s <= 1; s++) {
        for (int eb = 0; eb <= BX-1+1; eb++) {
            glBindTexture (GL_TEXTURE_1D, planx_[eb][s]);
            CHECK_GL_ERROR("glBindTexture");
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexImage1D (GL_TEXTURE_1D, 0, GL_RGBA, NX/2+1, 0, GL_RGBA, GL_FLOAT, NULL);
            CHECK_GL_ERROR("glTexImage1D");
        }
    }
    glGenTextures ((BY+1)*2, &plany_[0][0]);
    CHECK_GL_ERROR("glGenTextures");
    for (int s = 0; s <= 1; s++) {
        for (int eb=1; eb <= BY; eb++) {
            glBindTexture (GL_TEXTURE_1D, plany_[eb][s]);
            CHECK_GL_ERROR("glBindTexture");
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexImage1D (GL_TEXTURE_1D, 0, GL_RGBA, NY, 0, GL_RGBA, GL_FLOAT, NULL);
            CHECK_GL_ERROR("glTexImage1D");
        }
    }
}

void FFT::GeneratePlanX() {
    const int NX = size_.w;
    const int BX = log2x_;
    float *p = (float*)calloc (4*(NX/2+1), sizeof(float));

    for (int s=0; s<=1; s++) {
        int si = s*2-1; // si in {-1, 1}
        for (int eb=0; eb<=BX-1+1; eb++) {
            for (int x=0; x<NX/2+1; x++) {
                if (si==1 && eb==0)
                {
                    *(p + 4*x + 0) = (     x+0.5f)/(float)(NX/2+1);
                    *(p + 4*x + 1) = (NX/2-x+0.5f)/(float)(NX/2+1);
                    double w = si*M_PI*(x/(double)NX+0.25);
                    *(p + 4*x + 2) = (float)cos(w);
                    *(p + 4*x + 3) = (float)sin(w);
                }
                else if (si==-1 && eb==BX)
                {
                    if (x==0 || x==NX/2)
                    {
                        *(p + 4*x + 0) = 0;
                        *(p + 4*x + 1) = 0;
                    }
                    else
                    {
                        *(p + 4*x + 0) = (     x)/(float)(NX/2);
                        *(p + 4*x + 1) = (NX/2-x)/(float)(NX/2);
                    }
                    double w = si*M_PI*(x/(double)NX+0.25);
                    *(p + 4*x + 2) = (float)cos(w);
                    *(p + 4*x + 3) = (float)sin(w);
                }
                else if (x<NX/2)
                {
                    int l = 1<<eb;
                    int j = x%l;
                    double w = si*M_PI*j/l;
                    if (j<l/2)
                    {
                        if (eb==1)
                        {
                            *(p + 4*x + 0) = bitreverse(x    ,BX-1)/(float)(NX/2);
                            *(p + 4*x + 1) = bitreverse(x+l/2,BX-1)/(float)(NX/2);
                        }
                        else
                        {
                            *(p + 4*x + 0) = (x    )/(float)(NX/2);
                            *(p + 4*x + 1) = (x+l/2)/(float)(NX/2);
                        }
                    }
                    else
                    {
                        if (eb==1)
                        {
                            *(p + 4*x + 0) = bitreverse(x-l/2,BX-1)/(float)(NX/2);
                            *(p + 4*x + 1) = bitreverse(x    ,BX-1)/(float)(NX/2);
                        }
                        else
                        {
                            *(p + 4*x + 0) = (x-l/2)/(float)(NX/2);
                            *(p + 4*x + 1) = (x    )/(float)(NX/2);
                        }
                    }
                    *(p + 4*x + 2) = (float)cos(w);
                    *(p + 4*x + 3) = (float)sin(w);
                }
                else
                {
                    *(p + 4*x + 0) = 0;
                    *(p + 4*x + 1) = 0;
                    *(p + 4*x + 2) = 0;
                    *(p + 4*x + 3) = 0;
                }
            }
            glBindTexture (GL_TEXTURE_1D, planx_[eb][s]);
            glTexSubImage1D (GL_TEXTURE_1D, 0, 0, NX/2+1, GL_RGBA, GL_FLOAT, p);
        }
    }
    free(p);
} 

void FFT::GeneratePlanY() {
    const int NY = size_.h;
    const int BY = log2y_;
    float *p = (float*)calloc (4*NY, sizeof(float));

    for (int s=0; s<=1; s++) {
        int si = s*2-1;
        for (int eb=1; eb<=BY; eb++) {
            for (int x=0; x<NY; x++) {
                int l = 1<<eb;
                int j = x%l;
                double w = si*M_PI*j/l;
                if (j<l/2)
                {
                    if (eb==1)
                    {
                        *(p + 4*x + 0) = bitreverse(x    ,BY)/(float)NY;
                        *(p + 4*x + 1) = bitreverse(x+l/2,BY)/(float)NY;
                    }
                    else
                    {
                        *(p + 4*x + 0) = (x    )/(float)NY;
                        *(p + 4*x + 1) = (x+l/2)/(float)NY;
                    }
                }
                else
                {
                    if (eb==1)
                    {
                        *(p + 4*x + 0) = bitreverse(x-l/2,BY)/(float)NY;
                        *(p + 4*x + 1) = bitreverse(x    ,BY)/(float)NY;
                    }
                    else
                    {
                        *(p + 4*x + 0) = (x-l/2)/(float)NY;
                        *(p + 4*x + 1) = (x    )/(float)NY;
                    }
                }
                *(p + 4*x + 2) = (float)cos(w);
                *(p + 4*x + 3) = (float)sin(w);
            }

            glBindTexture (GL_TEXTURE_1D, plany_[eb][s]);
            glTexSubImage1D (GL_TEXTURE_1D, 0, 0, NY, GL_RGBA, GL_FLOAT, p);
        }
    }
    free (p);
}

void FFT::LoadShader() {
    Shader * shader = new Shader("fft2D_par");
    shader->Init(ShaderAttributes());
    shader_.reset(shader);
    uniforms_.dim_location = shader->UniformLocation("dim");
    uniforms_.tang_location = shader->UniformLocation("tang");
    uniforms_.tangsc_location = shader->UniformLocation("tangsc");
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

void FFT::Stage(int dim, int eb, int si, FrameBuffer* src, FrameBuffer* dst) {
    // Renaming variables to preserve copy-pasted code
    const int NX = size_.w;
    const int NY = size_.h;
    const int BX = log2x_;
    const int BY = log2y_;
    
    glBindFramebuffer(GL_FRAMEBUFFER, dst->framebuffer());
    CHECK_GL_ERROR("glBindFramebuffer");
    glViewport(0, 0, size_.w, size_.h);
    glUseProgram(shader_->program());
    CHECK_GL_ERROR("glUseProgram");
    glUniform1i(uniforms_.dim_location, dim);
    CHECK_GL_ERROR("glUniform1i");

    int tang;
    double tangsc;
    if (dim==1 && si==1 && eb==0) {
        tang = 1;
        tangsc = 0.5 * M_SQRT2;
    }
    else if (dim==1 && si==-1 && eb==BX) {
        tang = 1;
        tangsc = 0.5 / M_SQRT2;
    }
    else {
        tang = 0;
        tangsc = 0.0;
    }
    glUniform1i(uniforms_.tang_location, tang);
    glUniform1f(uniforms_.tangsc_location, (float)tangsc);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, src->texture());
    glUniform1i(uniforms_.state_tex_location, 0);

    glActiveTexture (GL_TEXTURE1);
    if (dim==1) {
        glBindTexture (GL_TEXTURE_1D, planx_[eb][(si+1)/2]);
    }
    else { // dim == 2
        glBindTexture (GL_TEXTURE_1D, plany_[eb][(si+1)/2]);
    }
    glUniform1i(uniforms_.plan_tex_location, 1);

    glBindVertexArray(vao_);
    CHECK_GL_ERROR("glBindVertexArray");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CHECK_GL_ERROR("glDrawArrays");
    
    // glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tb[ffto], 0);

    glUseProgram(0);
}

}  // namespace ca