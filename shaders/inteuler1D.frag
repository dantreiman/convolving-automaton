// SmoothLife
//
// 1D integrate euler shader


const float pi = 6.283185307;

uniform float dt, mode;

uniform sampler1D tex0;
uniform sampler1D tex1;


void main()
{
	float f, g, d;

	g = texture1D (tex0, gl_TexCoord[0].x).r;
	d = texture1D (tex1, gl_TexCoord[1].x).r;

	if (mode==0.0) f = d;
	else f = g + dt*d;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
