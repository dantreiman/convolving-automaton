#version 330 core
//
// Computes derivative and applies it to the state, all at once.
// outputs new state in fragColor.r
//
// integralTexture should contain the neighborhood integrals at each point.
// r = inner neighborhood integral, g = outer neighborhood integral
// stateTexture contains the current simulation state in the r channel.
//

layout(location = 0) out vec4 fragColor;

in vec2 texcoord;

uniform sampler2D integralTexture;
uniform sampler2D stateTexture;
uniform float b1, b2, d1, d2, sn, sm;
uniform float dt;

float func_smooth(float x, float a, float ea) {
    return 1.0 / (1.0 + exp((a - x) * 4.0 / ea));
}

float sigmoid_mix(float x, float y, float m) {
    return x * (1.0 - func_smooth(m, 0.5, sm)) + y * func_smooth(m, 0.5, sm);
}

float sigmoid_ab(float x, float a, float b) {
    return func_smooth(x, a, sn) * (1.0 - func_smooth(x, b, sn));
}

void main() {
    float st0 = texture(stateTexture, texcoord).r;
    vec2 nm = texture(integralTexture, texcoord).rb;
    float n = nm.x;
    float m = nm.y;
    float deriv = sigmoid_ab(n, sigmoid_mix (b1, d1, m), sigmoid_mix (b2, d2, m));
    //float st1 = st0;// + (deriv * dt);
    //fragColor = vec4(clamp(st1 * 2 - 1, 0, 1), 0.0, 0.0, 0.0);
    //fragColor = vec4(clamp(texcoord.x, 0, 1), 0.0, 0.0, 0.0);
    fragColor = vec4(n, 0, m, 0);
}
