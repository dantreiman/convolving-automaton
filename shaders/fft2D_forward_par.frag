#version 330 core
//
// Computes two DFTs at once.
// stateTex should contain two interleaved complex buffers.
// r+gi and b+ai
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
    vec4 input1 = texture(stateTex, newcoord1);
    vec4 input2 = texture(stateTex, newcoord2); 
    vec4 result;
    float imaginary = b.a;
    result.xz = b.b*input2.xz - imaginary*input2.yw;
    result.yw = imaginary*input2.xz + b.b*input2.yw;
    fragColor = result + input1;
}
