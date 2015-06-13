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
	vec4 mix = mod(a + b, 2);
    fragColor = mix;
}