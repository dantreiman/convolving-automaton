// SmoothLife
//
// draw snm function with color scheme


const float pi = 6.283185307;

uniform float colscheme, phase;
uniform float b1, b2, d1, d2, sn, sm;
uniform float mode, sigmode, sigtype, mixtype;
uniform sampler2D tex0;


float func_hard (float x, float a)
{
	if (x>=a) return 1.0; else return 0.0;
}

float func_linear (float x, float a, float ea)
{
	if (x < a-ea/2.0) return 0.0;
	else if (x > a+ea/2.0) return 1.0;
	else return (x-a)/ea + 0.5;
}

float func_hermite (float x, float a, float ea)
{
	if (x < a-ea/2.0) return 0.0;
	else if (x > a+ea/2.0) return 1.0;
	else
	{
		float m = (x-(a-ea/2.0))/ea;
		return m*m*(3.0-2.0*m);
	}
}

float func_sin (float x, float a, float ea)
{
	if (x < a-ea/2.0) return 0.0;
	else if (x > a+ea/2.0) return 1.0;
	else return sin(pi/2.0*(x-a)/ea)*0.5+0.5;
}

float func_smooth (float x, float a, float ea)
{
	return 1.0/(1.0+exp(-(x-a)*4.0/ea));
}

float func_atan (float x, float a, float ea)
{
	return atan((x-a)*(pi/2.0)/ea)/(pi/2.0)+0.5;
}

float func_atancos (float x, float a, float ea)
{
	return (atan((x-a)/ea)/(pi/4.0)*cos((x-a)*1.4)*1.1 + 1.0)/2.0;
}

float func_overshoot (float x, float a, float ea)
{
	return (1.0/(1.0+exp(-(x-a)*4.0/ea))-0.5)*(1.0+exp(-(x-a)*(x-a)/ea/ea))+0.5;
}


float sigmoid_ab (float x, float a, float b)
{
	     if (sigtype==0.0) return func_hard      (x, a    )*(1.0-func_hard      (x, b    ));
	else if (sigtype==1.0) return func_linear    (x, a, sn)*(1.0-func_linear    (x, b, sn));
	else if (sigtype==2.0) return func_hermite   (x, a, sn)*(1.0-func_hermite   (x, b, sn));
	else if (sigtype==3.0) return func_sin       (x, a, sn)*(1.0-func_sin       (x, b, sn));
	else if (sigtype==4.0) return func_smooth    (x, a, sn)*(1.0-func_smooth    (x, b, sn));
	else if (sigtype==5.0) return func_atan      (x, a, sn)*(1.0-func_atan      (x, b, sn));
	else if (sigtype==6.0) return func_atancos   (x, a, sn)*(1.0-func_atancos   (x, b, sn));
	else if (sigtype==7.0) return func_overshoot (x, a, sn)*(1.0-func_overshoot (x, b, sn));
	else if (sigtype==8.0) return 1.0/(1.0+exp(-(x-a)*4.0/sn)) * 1.0/(1.0+exp((x-b)*4.0/sn)) * (1.0-0.2*exp(-((x-(a+b)/2.0)*20.0)*((x-(a+b)/2.0)*20.0)));
	else if (sigtype==9.0) return 1.0/(1.0+exp(-(x-a)*4.0/sn)) * 1.0/(1.0+exp((x-b)*4.0/sn)) * (1.0+0.2*exp(-((x-(a+b)/2.0)*20.0)*((x-(a+b)/2.0)*20.0)));
}

float sigmoid_mix (float x, float y, float m)
{
	     if (mixtype==0.0) return x*(1.0-func_hard      (m, 0.5    )) + y*func_hard      (m, 0.5    );
	else if (mixtype==1.0) return x*(1.0-func_linear    (m, 0.5, sm)) + y*func_linear    (m, 0.5, sm);
	else if (mixtype==2.0) return x*(1.0-func_hermite   (m, 0.5, sm)) + y*func_hermite   (m, 0.5, sm);
	else if (mixtype==3.0) return x*(1.0-func_sin       (m, 0.5, sm)) + y*func_sin       (m, 0.5, sm);
	else if (mixtype==4.0) return x*(1.0-func_smooth    (m, 0.5, sm)) + y*func_smooth    (m, 0.5, sm);
	else if (mixtype==5.0) return x*(1.0-func_atan      (m, 0.5, sm)) + y*func_atan      (m, 0.5, sm);
	else if (mixtype==6.0) return x*(1.0-func_atancos   (m, 0.5, sm)) + y*func_atancos   (m, 0.5, sm);
	else if (mixtype==7.0) return x*(1.0-func_overshoot (m, 0.5, sm)) + y*func_overshoot (m, 0.5, sm);
}


float snm (vec2 nm)
{
	float n, m, f;

	n = nm.x;
	m = nm.y;

	     if (sigmode==1.0) f = mix (sigmoid_ab (n, b1, b2), sigmoid_ab (n, d1, d2), m);
	else if (sigmode==2.0) f = sigmoid_mix (sigmoid_ab (n, b1, b2), sigmoid_ab (n, d1, d2), m);
	else if (sigmode==3.0) f = sigmoid_ab (n, mix (b1, d1, m), mix (b2, d2, m));
	else  /*sigmode==4.0*/ f = sigmoid_ab (n, sigmoid_mix (b1, d1, m), sigmoid_mix (b2, d2, m));

	return f;
}


vec3 rainbow (float f)
{
	float r, g, b;

	     if (f>=0.0 && f<1.0) { r=1.0;   g=f-0.0; b=0.0;   }
	else if (f>=1.0 && f<2.0) { r=2.0-f; g=1.0;   b=0.0;   }
	else if (f>=2.0 && f<3.0) { r=0.0;   g=1.0;   b=f-2.0; }
	else if (f>=3.0 && f<4.0) { r=0.0;   g=4.0-f; b=1.0;   }
	else if (f>=4.0 && f<5.0) { r=f-4.0; g=0.0;   b=1.0;   }
	else if (f>=5.0 && f<6.0) { r=1.0;   g=0.0;   b=6.0-f; }
	else { r=0.0; g=0.0; b=0.0; }

	return vec3(r,g,b);
}

vec3 rainbowph (float f, float ph)
{
	return 0.5*sin(1.7*cos(pi*(f+vec3(0,1,2)/3.0+ph)))+0.5;
}


vec3 color (float f)
{
	//     if (colscheme==1.0) return vec3(f,.0,.0);		// red on black
	     if (colscheme==1.0) return rainbow (fract(phase)*6.0)*f;
	else if (colscheme==2.0) return vec3(f,f,f);		// white on black
	else if (colscheme==3.0) return vec3(1.0-f,1.0-f,1.0-f);		// black on white
	else if (colscheme==4.0) return rainbow (6.0*sqrt(sqrt(1.0-f)))*sqrt(sqrt(f));		// rainbow
	else if (colscheme==5.0) return mix (vec3(.5,.3,.0), vec3(.5,.75,.1), f);		// brown/green
	else if (colscheme==6.0) return mix (vec3(.5,.3,.0), mix (vec3(1.0,.95,.0), vec3(.3,.2,.0), f), sqrt(sqrt(f)));		// gold and brown
	else if (colscheme==7.0) return rainbowph (sqrt(sqrt(1.0-f)), phase)*sqrt(sqrt(f));		// rainbow with adjustable phase shift
}


void main()
{
	gl_FragColor.rgb = color (snm (gl_TexCoord[0].xy));
}
