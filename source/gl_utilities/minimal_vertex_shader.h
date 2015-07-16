#ifndef CONVOLVING_AUTOMATON_MINIMAL_VERTEX_SHADER_H_
#define CONVOLVING_AUTOMATON_MINIMAL_VERTEX_SHADER_H_

namespace ca {

const std::string minimal_vertex_shader_src = R"(
#version 330 core

layout(location = 0) in ivec2 position;

out vec2 texcoord;

void main()
{
    gl_Position.xy = position.xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    texcoord = (position.xy + 1.0) / 2.0;
}
)";


}  // namespace ca

#endif