#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 texcoord;

uniform vec2 scale;  // scale factor
uniform sampler2D stateFFT;
uniform sampler2D kernelsFFT;

void main()
{
    vec4 a = texture(stateFFT, texcoord);
    vec4 b = texture(kernelsFFT, texcoord) * scale.xxyy;
    fragColor.r = a.r*b.r - a.g*b.g;
    fragColor.g = a.r*b.g + a.g*b.r;
    fragColor.b = a.b*b.b - a.a*b.a;
    fragColor.a = a.b*b.a + a.a*b.b;
}
