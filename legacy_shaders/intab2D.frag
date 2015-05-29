// SmoothLife
//
// 2D integrate adams bashforth shader


const float pi = 6.283185307;

uniform float dt;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;


void main()
{
	float f, g;
	float f1, f2, f3;

	g = texture2D (tex0, gl_TexCoord[0].xy).r;
	f1 = texture2D (tex1, gl_TexCoord[1].xy).r;
	f2 = texture2D (tex2, gl_TexCoord[2].xy).r;
	f3 = texture2D (tex3, gl_TexCoord[3].xy).r;

	f = g + dt*(23.0*f1 - 16.0*f2 + 5.0*f3)/12.0;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
