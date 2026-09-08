#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec4 vColor;
out vec4 fColor;
void main() {
    gl_position = vec4(Pos.x, Pos.y, Pos.z, 1.0);
    fColor = vColor;
}