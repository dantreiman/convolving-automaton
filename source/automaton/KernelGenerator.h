#ifndef CONVOLVING_AUTOMATON_KERNEL_GENERATOR_H_
#define CONVOLVING_AUTOMATON_KERNEL_GENERATOR_H_

#include "Buffer.h"
#include "Vectors.h"

namespace ca {

class KernelGenerator {
 public:

    static void MakeCircularKernels(float inner_radius,
                                    Vec2<float> inner_offset,
                                    float outer_radius,
                                    Vec2<float> outer_offset,
                                    float border,
                                    Buffer2D<Vec4<float>>* kernel_buffer,
                                    float* inner_sum,
                                    float* outer_sum);

    static void MakeBoxKernels(float inner_radius,
                               Vec2<float> inner_offset,
                               float outer_radius,
                               Vec2<float> outer_offset,
                               float border,
                               Buffer2D<Vec4<float>>* kernel_buffer,
                               float* inner_sum,
                               float* outer_sum);

    static void MakeCircle(float radius,
                           float border,
                           Buffer2D<float>* kernel_buffer);

private:
    static void InterleaveAndShift(const Buffer2D<float>& inner_kernel,
                                   const Buffer2D<float>& outer_kernel,
                                   Buffer2D<Vec4<float>>* kernel_buffer);

};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_KERNEL_GENERATOR_H_
