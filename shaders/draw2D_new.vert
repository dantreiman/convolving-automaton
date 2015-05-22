#version 330 core

layout(location = 0) in ivec2 position;
out vec2 texCoord;

void main()
{
    gl_Position.xy = position.xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    texCoord = (position.xy + 1.0) / 2.0;
}