#version 330 core

out vec4 fragColor;

uniform int dimension;
uniform bool inverse;

uniform sampler2D stateTex;
uniform sampler1D planTex;

void main()
{
    vec2 texcoord = gl_FragCoord.xy - vec2(0.5, 0.5);
    float s = dimension == 0 ? texcoord.x : texcoord.y;
    vec4 b = texture(planTex, s);
    vec2 newcoord;
    newcoord.x = dimension == 0 ? b.r : texcoord.x;
    newcoord.y = dimension == 1 ? b.r : texcoord.y;
    vec4 Input1 = texture(stateTex, newcoord);
    newcoord.x = dimension == 0 ? b.g : texcoord.x;
    newcoord.y = dimension == 1 ? b.g : texcoord.y;
    vec4 Input2 = texture(stateTex, newcoord); 
    vec4 Res;
    float imag = inverse ? -b.a : b.a;
    Res.x = b.b*Input2.x - imag*Input2.y;
    Res.y = imag*Input2.x + b.b*Input2.y;
    imag = inverse ? -b.a : b.a;
    Res.z = b.b*Input2.z - imag*Input2.w;
    Res.w = imag*Input2.z + b.b*Input2.w;
    Res += Input1;
    Res.xy = inverse ? Res.xy / 2.0 : Res.xy;
    Res.zw = inverse ? Res.zw / 2.0 : Res.zw;
    fragColor = Res;
}
