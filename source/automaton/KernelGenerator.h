#ifndef CONVOLVING_AUTOMATON_KERNEL_GENERATOR_H_
#define CONVOLVING_AUTOMATON_KERNEL_GENERATOR_H_

#include "Buffer.h"
#include "Vectors.h"

namespace ca {

class KernelGenerator {
 public:

    static void MakeCircularKernels(float inner_radius,
                                    float outer_radius,
                                    float border,
                                    Buffer2D<Vec4<float>>* kernel_buffer,
                                    float* inner_sum,
                                    float* outer_sum);

    static void MakeCircularKernels(float inner_radius,
                                    Vec2<float> inner_offset,
                                    float outer_radius,
                                    Vec2<float> outer_offset,
                                    float border,
                                    Buffer2D<Vec4<float>>* kernel_buffer,
                                    float* inner_sum,
                                    float* outer_sum);

};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_KERNEL_GENERATOR_H_
