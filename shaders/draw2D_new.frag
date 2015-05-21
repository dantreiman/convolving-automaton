#version 330 core

layout(pixel_center_integer) in vec4 gl_FragCoord;
out vec4 fragColor;

uniform sampler2D stateTexture;

void main()
{
	vec4 color = texture(stateTexture, gl_FragCoord.st / 512, 0.0);
	// color.r = 1.0;
 // color.g = 1.0;
	// color.b = 1.0;
	color.a = 1.0;
    fragColor = color;
}