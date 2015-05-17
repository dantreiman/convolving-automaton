// SmoothLife
//
// 3D integrate runge kutta shader


const float pi = 6.283185307;

uniform float dt;

uniform sampler3D tex0;
uniform sampler3D tex1;
uniform sampler3D tex2;
uniform sampler3D tex3;
uniform sampler3D tex4;


void main()
{
	float f, g;
	float k1, k2, k3, k4;

	g = texture3D (tex0, gl_TexCoord[0].xyz).r;
	k1 = texture3D (tex1, gl_TexCoord[1].xyz).r;
	k2 = texture3D (tex2, gl_TexCoord[2].xyz).r;
	k3 = texture3D (tex3, gl_TexCoord[3].xyz).r;
	k4 = texture3D (tex4, gl_TexCoord[4].xyz).r;

	f = g + dt*(k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;

	gl_FragColor.r = clamp (f, 0.0, 1.0);
}
