#version 330 core
//
// Computes two DFTs at once.
// stateTex should contain two interleaved complex buffers.
// r+gi and b+ai
//
// This shader has been split in two to remove the conditional:
// fft2D_forward_par.frag, fft2D_inverse_par.frag
//

layout(location = 0) out vec4 fragColor;

in vec2 texcoord;

uniform int dimension;
uniform bool inverse;

uniform sampler2D stateTex;
uniform sampler1D planTex;

void main()
{
    float s = dimension == 0 ? texcoord.x : texcoord.y;
    vec4 b = texture(planTex, s);
    vec2 newcoord;
    newcoord.x = dimension == 0 ? b.r : texcoord.x;
    newcoord.y = dimension == 1 ? b.r : texcoord.y;
    vec4 input1 = texture(stateTex, newcoord);
    newcoord.x = dimension == 0 ? b.g : texcoord.x;
    newcoord.y = dimension == 1 ? b.g : texcoord.y;
    vec4 input2 = texture(stateTex, newcoord); 
    vec4 result;
    float imaginary = inverse ? -b.a : b.a;
    result.x = b.b*input2.x - imaginary*input2.y;
    result.y = imaginary*input2.x + b.b*input2.y;
    imaginary = inverse ? -b.a : b.a;
    result.z = b.b*input2.z - imaginary*input2.w;
    result.w = imaginary*input2.z + b.b*input2.w;
    result += input1;
    result.xy = inverse ? result.xy / 2.0 : result.xy;
    result.zw = inverse ? result.zw / 2.0 : result.zw;
    fragColor = result;
}
