// SmoothLife
//
// 2D integrate euler shader


const float pi = 6.283185307;

uniform float dt, mode;

uniform sampler2D tex0;
uniform sampler2D tex1;


void main()
{
	float f, g, d;

	g = texture2D (tex0, gl_TexCoord[0].xy).r;
	d = texture2D (tex1, gl_TexCoord[1].xy).r;

	if (mode==0.0) f = d;
	else f = g + dt*d;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
