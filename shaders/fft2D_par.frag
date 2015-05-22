#version 330 core

in vec2 texCoord;
out vec4 fragColor;

uniform int dim, tang;
uniform float tangsc;

uniform sampler2D stateTex;
uniform sampler1D planTex;

// Single complex multiplication
vec2 cmul (vec2 a, vec2 b)
{
    return vec2 (a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}

// Distributed complex multiplication
vec4 cmul2s (vec4 a, vec2 b)
{
    return vec4 (a.r*b.r - a.g*b.g, a.r*b.g + a.g*b.r,
                 a.b*b.r - a.a*b.g, a.b*b.g + a.a*b.r);
}

// 2-wide parallel complex multiplication
vec4 cmul2 (vec4 a, vec4 b)
{
    return vec4 (a.r*b.r - a.g*b.g, a.r*b.g + a.g*b.r,
                 a.b*b.b - a.a*b.a, a.b*b.a + a.a*b.b);
}

void main()
{
    vec4 a, b;
    vec2 v;
    vec4 p;

    v = texCoord.xy;

    if (dim==1)
    {
        p = texture(planTex, v.x).rgba;
        a = texture(stateTex, vec2 (p.r, v.y)).rgba;
        b = texture(stateTex, vec2 (p.g, v.y)).rgba;
        if (tang==1)
        {
            b.g = -b.g; // complex conjugate
            b.a = -b.a; // complex conjugate
            fragColor = (a+b + cmul2s(a-b, p.ba))*tangsc;
        }
        else
        {
			const float INV_SQRT2 = 1.0/sqrt(2.0);
            fragColor.r = (a.r + p.b*b.r - p.a*b.g)*INV_SQRT2;
            fragColor.g = (a.g + p.b*b.g + p.a*b.r)*INV_SQRT2;
            fragColor.b = (a.b + p.b*b.b - p.a*b.b)*INV_SQRT2;
            fragColor.a = (a.a + p.b*b.a + p.a*b.a)*INV_SQRT2;
        }
    }
    else //if (dim==2)
    {
		const float INV_SQRT2 = 1.0/sqrt(2.0);
        p = texture(planTex, v.y).rgba;
        a = texture(stateTex, vec2 (v.x, p.r)).rgba;
        b = texture(stateTex, vec2 (v.x, p.g)).rgba;
        //fragColor.rg = (a + cmul (p.ba,b))*(1.0/sqrt(2.0));
        fragColor.r = (a.r + p.b*b.r - p.a*b.g)*INV_SQRT2;
        fragColor.g = (a.g + p.b*b.g + p.a*b.r)*INV_SQRT2;
        fragColor.b = (a.b + p.b*b.b - p.a*b.a)*INV_SQRT2;
        fragColor.a = (a.a + p.b*b.a + p.a*b.b)*INV_SQRT2;
    }

}
