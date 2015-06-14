#version 330 core
//
// Draws a shape.
//

in vec2 texcoord;
out vec4 fragColor;
uniform sampler2D mixA;
uniform sampler2D mixB;

void main()
{
    vec4 a = texture(mixA, texcoord);
    vec4 b = texture(mixB, texcoord);
    float mix = (a.r + b.r) * (1-b.g);
    fragColor = vec4(mix, 0.0, 0.0, 1.0);
}