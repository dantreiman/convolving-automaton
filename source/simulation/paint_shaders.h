#ifndef CONVOLVING_AUTOMATON_PAINT_SHADERS_H_
#define CONVOLVING_AUTOMATON_PAINT_SHADERS_H_

#include <string>

namespace ca {

const std::string paint_vert_src = R"(
#version 330 core
//

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;

out vec2 texcoord;

void main()
{
    gl_Position.xy = position.xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    texcoord = texture_coordinate;
})";


const std::string paint_frag_src = R"(
#version 330 core
//
// Draws textured 2D polys.
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
