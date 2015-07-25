#ifndef CONVOLVING_AUTOMATON_PAINT_SHADERS_H_
#define CONVOLVING_AUTOMATON_PAINT_SHADERS_H_

#include <string>

namespace ca {

const std::string paint_frag_src = R"(
#version 330 core
//
// Draws textured 2D polys with additive blending.
//

layout(location = 0) out vec4 fragColor;

in vec2 texcoord;

uniform sampler2D brush;

void main()
{
    vec4 brush_color = texture(brush, texcoord);
    fragColor =  brush_color;
}
)";

}  // namespace ca

#endif
