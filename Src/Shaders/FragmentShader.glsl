#version 330 core
in vec4 fColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(fColor.r, fColor.g, fColor.b, fColor.a);
}
