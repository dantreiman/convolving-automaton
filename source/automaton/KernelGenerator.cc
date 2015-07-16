#include "KernelGenerator.h"

#include <cmath>

namespace {

float func_linear (float x, float a, float b) {
    if (x < a - b / 2.0) return 0.0;
    else if (x > a + b / 2.0) return 1.0;
    else return (x - a + b / 2.0) / b;
}

float CircularKernel(float radius,
                     ca::Vec2<float> offset,
                     float border,
                     ca::Buffer2D<float> *buffer) {
    const ca::Size& size = buffer->size();
    const int tx = (size.w / 2) + offset.x;
    const int ty = (size.h / 2) + offset.y;
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

float RingKernel(float inner_radius,
                 float outer_radius,
                 ca::Vec2<float> offset,
                 float border,
                 ca::Buffer2D<float> * buffer) {
    const ca::Size& size = buffer->size();
    const int tx = size.w / 2 + offset.x;
    const int ty = size.h / 2 + offset.y;
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

}  // namespace


namespace ca {


void KernelGenerator::MakeCircularKernels(float inner_radius,
                                          float outer_radius,
                                          float border,
                                          Buffer2D<Vec4<float>>* kernel_buffer,
                                          float* inner_sum,
                                          float* outer_sum) {
    MakeCircularKernels(inner_radius,
                        Vec2<float>(0, 0),
                        outer_radius,
                        Vec2<float>(0, 0),
                        border,
                        kernel_buffer,
                        inner_sum,
                        outer_sum);
}

void KernelGenerator::MakeCircularKernels(float inner_radius,
                                          Vec2<float> inner_offset,
                                          float outer_radius,
                                          Vec2<float> outer_offset,
                                          float border,
                                          Buffer2D<Vec4<float>>* kernel_buffer,
                                          float* inner_sum,
                                          float* outer_sum) {
    const Size& world_size = kernel_buffer->size();
    Buffer2D<float> inner_kernel(world_size);
    *inner_sum = CircularKernel(inner_radius,
                                inner_offset,
                                border,
                                &inner_kernel);
    Buffer2D<float> outer_kernel(world_size);
    *outer_sum = RingKernel(inner_radius,
                            outer_radius,
                            outer_offset,
                            border,
                            &outer_kernel);
    Size half_size = Size(world_size.w / 2, world_size.h / 2);
    for (int x = 0; x < world_size.w; x++) {
        for (int y = 0; y < world_size.h; y++) {
            // Perform FFT shift
            const int shift_x = (x + half_size.w) % world_size.w;
            const int shift_y = (y + half_size.h) % world_size.h;
            // Interleave both kernels using r and b channels of the same image
            kernel_buffer->set(x, y, Vec4<float>(inner_kernel.get(shift_x, shift_y), 0,
                                                 outer_kernel.get(shift_x, shift_y), 0));
        }
    }
}


} // namespace ca