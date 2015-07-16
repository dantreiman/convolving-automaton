#ifndef CONVOLVING_AUTOMATON_FFT_SHADERS_H_
#define CONVOLVING_AUTOMATON_FFT_SHADERS_H_

#include <string>

namespace ca {

const std::string fft2d_forward_parallel_frag_src = R"(
#version 330 core
//
// Computes two DFTs at once.
// stateTex should contain two interleaved complex buffers.
// r+gi and b+ai
//

layout(location = 0) out vec4 fragColor;

in vec2 texcoord;

uniform int dimension;
uniform sampler2D stateTex;
uniform sampler1D planTex;

void main()
{
    float s = dimension == 0 ? texcoord.x : texcoord.y;
    vec4 b = texture(planTex, s);
    vec2 newcoord1;
    vec2 newcoord2;
    if (dimension == 0) {
        newcoord1 = vec2(b.r, texcoord.y);
        newcoord2 = vec2(b.g, texcoord.y);
    }
    else {
        newcoord1 = vec2(texcoord.x, b.r);
        newcoord2 = vec2(texcoord.x, b.g);
    }
    vec4 input1 = texture(stateTex, newcoord1);
    vec4 input2 = texture(stateTex, newcoord2); 
    vec4 result;
    float imaginary = b.a;
    result.xz = b.b*input2.xz - imaginary*input2.yw;
    result.yw = imaginary*input2.xz + b.b*input2.yw;
    fragColor = result + input1;
}
)";


const std::string fft2d_inverse_parallel_frag_src = R"(
#version 330 core
//
// Computes two inverse DFTs at once.
// stateTex should contain two interleaved complex buffers.
// r+gi and b+ai
//
// This is a spin-off from fft2D_par.frag to remove the per-pixel conditional.
//

layout(location = 0) out vec4 fragColor;

in vec2 texcoord;

uniform int dimension;
uniform sampler2D stateTex;
uniform sampler1D planTex;

void main()
{
    float s = dimension == 0 ? texcoord.x : texcoord.y;
    vec4 b = texture(planTex, s);
    vec2 newcoord1;
    vec2 newcoord2;
    if (dimension == 0) {
        newcoord1 = vec2(b.r, texcoord.y);
        newcoord2 = vec2(b.g, texcoord.y);
    }
    else {
        newcoord1 = vec2(texcoord.x, b.r);
        newcoord2 = vec2(texcoord.x, b.g);
    }
    vec4 input1 = texture(stateTex, newcoord1);
    vec4 input2 = texture(stateTex, newcoord2); 
    vec4 result;
    float imaginary = -b.a;
    result.x = b.b*input2.x - imaginary*input2.y;
    result.y = imaginary*input2.x + b.b*input2.y;
    result.z = b.b*input2.z - imaginary*input2.w;
    result.w = imaginary*input2.z + b.b*input2.w;
    result += input1;
    fragColor = result / 2.0;
}
)";


}  // namespace ca

#endif