#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 texcoord;

uniform vec2 scale;  // scale factor
uniform sampler2D stateFFT;
uniform sampler2D kernelsFFT;

void main()
{
    vec2 a = texture(stateFFT, texcoord).rg;
    vec4 b = texture(kernelsFFT, texcoord);// * scale.xxyy;
    fragColor.r = a.r*b.r - a.g*b.g;
    fragColor.g = a.r*b.g + a.g*b.r;
    fragColor.b = a.r*b.b - a.g*b.a;
    fragColor.a = a.r*b.a + a.g*b.b;
}