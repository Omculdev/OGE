#include "Rendering/Shaders/VertexShader.hpp"
#include <GLAD/glad.h>
VertexShader::VertexShader() : BasicShader(GL_VERTEX_SHADER) {}
VertexShader::VertexShader(const char* source) : BasicShader(GL_VERTEX_SHADER, source) {}