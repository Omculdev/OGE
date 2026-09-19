#version 330 core

layout (location = 0) in vec3 position_input;
layout (location = 1) in vec4 color_input;

out vec4 color_output;

void main() {
    gl_Position = vec4(position_input, 1.0);   
    color_output = color_input;
}