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
    vec2 newcoord1;
    vec2 newcoord2;
    if (dimension == 0) {
        newcoord1 = vec2(b.r, texcoord.y);
        newcoord2 = vec2(b.g, texcoord.y);
    }
    else {
        newcoord1 = vec2(texcoord.x, b.r);
        newcoord2 = vec2(texcoord.x, b.g);
    }
    vec2 input1 = texture(stateTex, newcoord1).rg;
    vec2 input2 = texture(stateTex, newcoord2).rg; 
    vec2 result;
    float imaginary = b.a;
    result.x = b.b*input2.x - imaginary*input2.y;
    result.y = imaginary*input2.x + b.b*input2.y;
    fragColor.rg = result + input1;
}
