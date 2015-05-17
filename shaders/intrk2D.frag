// SmoothLife
//
// 2D integrate runge kutta shader


const float pi = 6.283185307;

uniform float dt;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;


void main()
{
	float f, g;
	float k1, k2, k3, k4;

	g = texture2D (tex0, gl_TexCoord[0].xy).r;
	k1 = texture2D (tex1, gl_TexCoord[1].xy).r;
	k2 = texture2D (tex2, gl_TexCoord[2].xy).r;
	k3 = texture2D (tex3, gl_TexCoord[3].xy).r;
	k4 = texture2D (tex4, gl_TexCoord[4].xy).r;

	f = g + dt*(k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
