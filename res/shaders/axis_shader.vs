#version 330 core
layout (location = 0) in vec2 aPos;
uniform float x_offset;
uniform float x_scale;
uniform float y_offset;
uniform float y_scale;

void main()
{
    gl_Position = vec4((aPos.x + x_offset) * x_scale, (aPos.y + y_offset) * y_scale, 0.0, 1.0);
}
