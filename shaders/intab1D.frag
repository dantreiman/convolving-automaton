// SmoothLife
//
// 1D integrate adams bashforth shader


const float pi = 6.283185307;

uniform float dt;

uniform sampler1D tex0;
uniform sampler1D tex1;
uniform sampler1D tex2;
uniform sampler1D tex3;


void main()
{
	float f, g;
	float f1, f2, f3;

	g = texture1D (tex0, gl_TexCoord[0].x).r;
	f1 = texture1D (tex1, gl_TexCoord[1].x).r;
	f2 = texture1D (tex2, gl_TexCoord[2].x).r;
	f3 = texture1D (tex3, gl_TexCoord[3].x).r;

	f = g + dt*(23.0*f1 - 16.0*f2 + 5.0*f3)/12.0;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
