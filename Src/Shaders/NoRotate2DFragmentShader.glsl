#version 330 core

in vec4 color_output;

out vec4 fragment_color;

void main() {
    fragment_color = color_output;
}