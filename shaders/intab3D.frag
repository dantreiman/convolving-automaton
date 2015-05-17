// SmoothLife
//
// 3D integrate adams bashforth shader


const float pi = 6.283185307;

uniform float dt;

uniform sampler3D tex0;
uniform sampler3D tex1;
uniform sampler3D tex2;
uniform sampler3D tex3;


void main()
{
	float f, g;
	float f1, f2, f3;

	g = texture3D (tex0, gl_TexCoord[0].xyz).r;
	f1 = texture3D (tex1, gl_TexCoord[1].xyz).r;
	f2 = texture3D (tex2, gl_TexCoord[2].xyz).r;
	f3 = texture3D (tex3, gl_TexCoord[3].xyz).r;

	f = g + dt*(23.0*f1 - 16.0*f2 + 5.0*f3)/12.0;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
