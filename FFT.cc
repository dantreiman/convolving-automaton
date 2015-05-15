#include "FFT.h"

#include <cmath>
#include "log.h"

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
    GeneratePlanX();
    GeneratePlanY();
}


void FFT::GeneratePlanTextures() {
    const int NX = size_.w,
              NY = size_.h,
              BX = log2x_,
              BY = log2y_;
                
    glGenTextures ((BX-1+2)*2, &planx[0][0]);
    for (int s = 0; s <= 1; s++) {
        for (int eb = 0; eb <= BX-1+1; eb++) {
            glBindTexture (GL_TEXTURE_1D, planx[eb][s]);
            CHECK_GL_ERROR("glBindTexture");
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf (GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexImage1D (GL_TEXTURE_1D, 0, GL_RGBA, NX/2+1, 0, GL_RGBA, GL_FLOAT, NULL);
            CHECK_GL_ERROR("glTexImage1D");
        }
    }
    glGenTextures ((BY+1)*2, &plany[0][0]);
    for (int s = 0; s <= 1; s++) {
        for (int eb=1; eb <= BY; eb++) {
            glBindTexture (GL_TEXTURE_1D, plany[eb][s]);
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
            glBindTexture (GL_TEXTURE_1D, planx[eb][s]);
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

            glBindTexture (GL_TEXTURE_1D, plany[eb][s]);
            glTexSubImage1D (GL_TEXTURE_1D, 0, 0, NY, GL_RGBA, GL_FLOAT, p);
        }
    }
    free (p);
}


}  // namespace ca