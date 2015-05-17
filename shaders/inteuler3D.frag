// SmoothLife
//
// 3D integrate euler shader


const float pi = 6.283185307;

uniform float dt, mode;

uniform sampler3D tex0;
uniform sampler3D tex1;


void main()
{
	float f, g, d;

	g = texture3D (tex0, gl_TexCoord[0].xyz).r;
	d = texture3D (tex1, gl_TexCoord[1].xyz).r;

	if (mode==0.0) f = d;
	else f = g + dt*d;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
