#version 330 core

in ivec2 position;
out vec2 texCoord;

void main()
{
    gl_Position.xy = position.xy;
    gl_Position.z = 0.0f;
    gl_Position.w = 1.0f;
    texCoord = position.xy;
}