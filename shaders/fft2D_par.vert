#version 330 core

layout(location = 0) in ivec2 position;

void main()
{
    gl_Position.xy = position.xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
}
