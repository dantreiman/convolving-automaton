// SmoothLife
//
// 1D integrate runge kutta shader


const float pi = 6.283185307;

uniform float dt;

uniform sampler1D tex0;
uniform sampler1D tex1;
uniform sampler1D tex2;
uniform sampler1D tex3;
uniform sampler1D tex4;


void main()
{
	float f, g;
	float k1, k2, k3, k4;

	g = texture1D (tex0, gl_TexCoord[0].x).r;
	k1 = texture1D (tex1, gl_TexCoord[1].x).r;
	k2 = texture1D (tex2, gl_TexCoord[2].x).r;
	k3 = texture1D (tex3, gl_TexCoord[3].x).r;
	k4 = texture1D (tex4, gl_TexCoord[4].x).r;

	f = g + dt*(k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
