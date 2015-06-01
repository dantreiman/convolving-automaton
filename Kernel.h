#ifndef CONVOLVING_AUTOMATON_KERNEL_H_
#define CONVOLVING_AUTOMATON_KERNEL_H_

#include "Buffer.h"

namespace ca {

// Returns the sum, writes kernel into buffer
float CircularKernel(Buffer2D<float> *buffer,
                     float radius,
                     float border);

// Returns the sum, writes kernel into buffer
float RingKernel(Buffer2D<float> * buffer,
                float inner_radius,
                float outer_radius,
                float border);

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_KERNEL_H_
