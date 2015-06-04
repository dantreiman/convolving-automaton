#version 330 core
//
// Computes a single forward FFT.
// stateTex should contain a single real value in the r channel.
// Output is stored as r + gi
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
    vec2 newcoord;
    newcoord.x = dimension == 0 ? b.r : texcoord.x;
    newcoord.y = dimension == 1 ? b.r : texcoord.y;
    vec2 input1 = texture(stateTex, newcoord).rg;
    newcoord.x = dimension == 0 ? b.g : texcoord.x;
    newcoord.y = dimension == 1 ? b.g : texcoord.y;
    vec2 input2 = texture(stateTex, newcoord).rg; 
    vec4 result;
    float imaginary = inverse ? -b.a : b.a;
    result.x = b.b*input2.x - imaginary*input2.y;
    result.y = imaginary*input2.x + b.b*input2.y;
    result += input1;
    fragColor = result;
}
