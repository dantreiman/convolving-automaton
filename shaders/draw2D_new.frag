#version 330 core
//
// Draws the state to the screen.
// Expects stateTexture to contain the state in the r channel.
//

in vec2 texcoord;
out vec4 fragColor;

uniform sampler2D stateTexture;


vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main()
{
    vec3 hsv = vec3(texture(stateTexture, texcoord).r * 2,
                    1.0,
                    1.0);
    vec3 rgb = hsv2rgb(hsv);
    fragColor = vec4(rgb.r, rgb.g, rgb.b, 1.0);
}