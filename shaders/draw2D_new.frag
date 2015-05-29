#version 330 core

in vec2 texcoord;
out vec4 fragColor;

uniform sampler2D stateTexture;

void main()
{
    vec4 color = texture(stateTexture, texcoord, 0.0);
    color.a = 1.0;
    fragColor = color;
}