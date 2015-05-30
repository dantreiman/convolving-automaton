#version 330 core
//
// Draws the state to the screen.
// Expects stateTexture to contain the state in the r channel.
//

in vec2 texcoord;
out vec4 fragColor;

uniform sampler2D stateTexture;

void main()
{
    vec4 color = texture(stateTexture, texcoord);
    color.a = 1.0;
    fragColor = color;
}