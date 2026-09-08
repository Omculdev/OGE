#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float ambientlight;
uniform float brightness;
uniform vec3 lightposition;
uniform vec3 lightcolor;

layout (location = 0) in vec3 vertexposition;
layout (location = 1) in vec3 colorin;
layout (location = 2) in vec3 normal;

out vec4 colorout;


void main() {
    vec3 distancetolightsource = normalize(vertexposition - lightposition);
    float difflight = max(dot(distancetolightsource, normal), 0.0);
    vec3 diffuse = difflight * lightcolor * colorin;
    gl_Position = vec4(vertexposition, 1.0);
    colorout = projection * view * model * vec4(diffuse, 1.0); 
}