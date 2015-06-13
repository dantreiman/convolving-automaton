#version 330 core
//
// Draws the state to the screen.
// Expects stateTexture to contain the state in the r channel.
//

in vec2 texcoord;
out vec4 fragColor;

uniform vec4 backgroundColor;
uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;
uniform vec4 color4;
uniform sampler2D stateTexture;

void main()
{
    float colorStop1 = .3;
    float colorStop2 = .6;
    float value = texture(stateTexture, texcoord).r;
    vec4 color = backgroundColor;
    if (value > 0.0) {
        color = mix(color1, color2, smoothstep(0, colorStop1, value));
        color = mix(color, color3, smoothstep(colorStop1, colorStop2, value));
        color = mix(color, color4, smoothstep(colorStop2, 1.0, value));
    }
    fragColor = color;
}