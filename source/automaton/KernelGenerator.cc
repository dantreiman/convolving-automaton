#include "KernelGenerator.h"

#include <cmath>

namespace {

float func_linear (float x, float a, float b) {
    if (x < a - b / 2.0) return 0.0;
    else if (x > a + b / 2.0) return 1.0;
    else return (x - a + b / 2.0) / b;
}


class Circle {
 public:
    Circle(float radius, float border) : radius_(radius), border_(border) {}
    
    float operator () (int x, int y) const {
        const float d = hypotf(x, y);
        return 1 - func_linear(d, radius_, border_);
    }

 private:
    float radius_;
    float border_;
};


class Ring {
 public:
    Ring(float inner_radius, float outer_radius, float border) :
        inner_radius_(inner_radius),
        outer_radius_(outer_radius),
        border_(border) {}
    
    float operator () (int x, int y) const {
        const float d = hypotf(x, y);
        return func_linear(d, inner_radius_, border_) * (1 - func_linear(d, outer_radius_, border_));
    }

 private:
    float inner_radius_;
    float outer_radius_;
    float border_;
};


class Box {
 public:
    Box(float radius, float border) : radius_(radius), border_(border) {}
    
    float operator () (int x, int y) const {
        const float d = fmax(abs(x), abs(y));
        return 1 - func_linear(d, radius_, border_);
    }

 private:
    float radius_;
    float border_;
};


class OuterBox {
 public:
    OuterBox(float inner_radius, float outer_radius, float border) :
        inner_radius_(inner_radius),
        outer_radius_(outer_radius),
        border_(border) {}
    
    float operator () (int x, int y) const {
        const float d = fmax(abs(x), abs(y));
        return func_linear(d, inner_radius_, border_) * (1 - func_linear(d, outer_radius_, border_));
    }

 private:
    float inner_radius_;
    float outer_radius_;
    float border_;
};


// Generate a kernel using an arbitrary functor to compute
// the value at each point
template <class F>
float GenerateKernel(F f,
                     ca::Vec2<float> offset,
                     ca::Buffer2D<float> *buffer) {
    const ca::Size& size = buffer->size();
    const int tx = (size.w / 2) + offset.x;
    const int ty = (size.h / 2) + offset.y;
    float sum = 0;
    for (int y = 0; y < size.h; y++) {
        for (int x = 0; x < size.w; x++) {
            const float value = f(x - tx, y - ty);
            buffer->set(x, y, value);
            sum += value;
        }
    }
    return sum;
}


}  // namespace


namespace ca {


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
    *inner_sum = GenerateKernel(Circle(inner_radius, border),
                                inner_offset,
                                &inner_kernel);
    Buffer2D<float> outer_kernel(world_size);
    *outer_sum = GenerateKernel(Ring(inner_radius, outer_radius, border),
                                outer_offset,
                                &outer_kernel);
    InterleaveAndShift(inner_kernel, outer_kernel, kernel_buffer);
}


void KernelGenerator::MakeBoxKernels(float inner_radius,
                                     Vec2<float> inner_offset,
                                     float outer_radius,
                                     Vec2<float> outer_offset,
                                     float border,
                                     Buffer2D<Vec4<float>>* kernel_buffer,
                                     float* inner_sum,
                                     float* outer_sum) {
    const Size& world_size = kernel_buffer->size();
    Buffer2D<float> inner_kernel(world_size);
    *inner_sum = GenerateKernel(Box(inner_radius, border),
                                inner_offset,
                                &inner_kernel);
    Buffer2D<float> outer_kernel(world_size);
    *outer_sum = GenerateKernel(OuterBox(inner_radius, outer_radius, border),
                                outer_offset,
                                &outer_kernel);
    InterleaveAndShift(inner_kernel, outer_kernel, kernel_buffer);
    
}


void KernelGenerator::MakeCircle(float radius,
                                 float border,
                                 Buffer2D<float>* kernel_buffer) {
    GenerateKernel(Circle(radius, border),
                   Vec2<float>(0, 0),
                   kernel_buffer);
}


void KernelGenerator::InterleaveAndShift(const Buffer2D<float>& inner_kernel,
                                         const Buffer2D<float>& outer_kernel,
                                         Buffer2D<Vec4<float>>* kernel_buffer) {
    const Size& world_size = kernel_buffer->size();
    const Size half_size = Size(world_size.w / 2, world_size.h / 2);
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