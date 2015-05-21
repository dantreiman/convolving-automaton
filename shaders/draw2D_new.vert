#version 330 core

in vec2 position;

void main()
{
    gl_Position.xy = position.xy;
    gl_Position.z = 0.0f;
    gl_Position.w = 1.0f;
}