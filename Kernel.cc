#include "Kernel.h"

#include <cmath>

namespace {

float func_linear (float x, float a, float b) {
    if (x < a - b / 2.0) return 0.0;
    else if (x > a + b / 2.0) return 1.0;
	else return (x - a + b / 2.0) / b;
}
    
}


namespace ca {

float CircularKernel(Buffer2D<float> *buffer,
                     float radius,
                     float border) {
    const Size& size = buffer->size();
    const int tx = size.w / 2;
    const int ty = size.h / 2;
    float sum = 0;
    for (int y = 0; y < size.h; y++) {
        for (int x = 0; x < size.w; x++) {
            const float d = hypotf(x - tx, y - ty);
            const float value = 1 - func_linear(d, radius, border);
            buffer->set(x, y, value);
            sum += value;
        }
    }
    return sum;
}

float RingKernel(Buffer2D<float> * buffer,
                float inner_radius,
                float outer_radius,
                float border) {
    const Size& size = buffer->size();
    const int tx = size.w / 2;
    const int ty = size.h / 2;
    float sum = 0;
    for (int y = 0; y < size.h; y++) {
        for (int x = 0; x < size.w; x++) {
            const float d = hypotf(x - tx, y - ty);
            const float value = func_linear(d, inner_radius, border) * (1 - func_linear(d, outer_radius, border));
            buffer->set(x, y, value);
            sum += value;
        }
    }
    return sum;
}


// n = func_kernel (d, ri, border) * ( 1 - func_kernel(l, ra, border));


// void makekernel (int kr, int kd)
// {
//  int ix, iy, iz, x, y, z;
//  double l, n, m;
//  float *ar, *ad;
//  int Ra;
//  double ri, bb;
// 
//  ad = (float*)calloc (NX*NY, sizeof(float));
//  if (ad==0) { fprintf (logfile, "ad failed\n"); fflush (logfile); return; }
// 
//  ar = (float*)calloc (NX*NY, sizeof(float));
//  if (ar==0) { fprintf (logfile, "ar failed\n"); fflush (logfile); return; }
// 
//  ri = ra/rr;
//  bb = ra/rb;
// 
//  //Ra = (int)(ra+bb/2+1.0);
//  Ra = (int)(ra*2);
// 
//  kflr = 0.0;
//  kfld = 0.0;
// 
//  for (iz=0; iz<NZ; iz++)
//  {
//      memset (ad, 0, NX*NY*sizeof(float));
//      memset (ar, 0, NX*NY*sizeof(float));
//      if (dims>2)
//      {
//          if (iz<NZ/2) z = iz; else z = iz-NZ;
//      }
//      else
//      {
//          z = 0;
//      }
//      if (z>=-Ra && z<=Ra)
//      {
//          for (iy=0; iy<NY; iy++)
//          {
//              if (dims>1)
//              {
//                  if (iy<NY/2) y = iy; else y = iy-NY;
//              }
//              else
//              {
//                  y = 0;
//              }
//              if (y>=-Ra && y<=Ra)
//              {
//                  for (ix=0; ix<NX; ix++)
//                  {
//                      if (ix<NX/2) x = ix; else x = ix-NX;
//                      if (x>=-Ra && x<=Ra)
//                      {
//                          //l = pnorm (x,y,z,0.5);
//                          //l = pnorm (x,y,z,1);
//                          l = pnorm (x,y,z,2);
//                          //l = pnorm (x,y,z,20);
//                          
//                          m = 1-func_kernel (l, ri, bb);
//                          n = func_kernel (l, ri, bb) * (1-func_kernel (l, ra, bb));
//                          
//                          /*
//                          // angle dependent kernel
//                          double w;
//                          w = atan2 (x, y);
//                          n *= 0.5*sin(6*w)+0.5;
//                          */
// 
//                          /*
//                          // gauss kernel (profile is a gaussian instead of flat)
//                          const double mc = 2;
//                          const double nc = 4;
// 
//                          double r;
//                          
//                          r = l/(ri/mc);
//                          m = exp(-r*r);
// 
//                          r = l-(ra+ri)/2;
//                          r /= (ra-ri)/nc;
//                          n = exp(-r*r);
//                          */
// 
//                          *(ad + iy*NX + ix) = (float)m;
//                          *(ar + iy*NX + ix) = (float)n;
//                          kflr += n;
//                          kfld += m;
//                      }   // if ix
//                  }   // for ix
//              }   // if iy
//          }   // for iy
//      }   // if iz
// 
//      if (dims==1)
//      {
//          glBindTexture (GL_TEXTURE_1D, tr[kd]);
//          glTexSubImage1D (GL_TEXTURE_1D, 0, 0, NX, GL_RED, GL_FLOAT, ad);
// 
//          glBindTexture (GL_TEXTURE_1D, tr[kr]);
//          glTexSubImage1D (GL_TEXTURE_1D, 0, 0, NX, GL_RED, GL_FLOAT, ar);
//      }
//      else if (dims==2)
//      {
//          glBindTexture (GL_TEXTURE_2D, tr[kd]);
//          glTexSubImage2D (GL_TEXTURE_2D, 0, 0,0, NX,NY, GL_RED, GL_FLOAT, ad);
// 
//          glBindTexture (GL_TEXTURE_2D, tr[kr]);
//          glTexSubImage2D (GL_TEXTURE_2D, 0, 0,0, NX,NY, GL_RED, GL_FLOAT, ar);
//      }
//      else // dims==3
//      {
//          glBindTexture (GL_TEXTURE_3D, tr[kd]);
//          glTexSubImage3D (GL_TEXTURE_3D, 0, 0,0,iz, NX,NY,1, GL_RED, GL_FLOAT, ad);
// 
//          glBindTexture (GL_TEXTURE_3D, tr[kr]);
//          glTexSubImage3D (GL_TEXTURE_3D, 0, 0,0,iz, NX,NY,1, GL_RED, GL_FLOAT, ar);
//      }
//  }   // for iz
// 
//  free (ar);
//  free (ad);
// 
//  fprintf (logfile, "ra=%lf rr=%lf rb=%lf ri=%lf bb=%lf kflr=%lf kfld=%lf kflr/kfld=%lf\n", ra, rr, rb, ri, bb, kflr, kfld, kflr/kfld); fflush (logfile);
// }

} // namespace ca