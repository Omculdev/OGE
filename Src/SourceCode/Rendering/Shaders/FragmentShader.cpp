#include "Rendering/Shaders/FragmentShader.hpp"
#include <GLAD/glad.h>
FragmentShader::FragmentShader() : BasicShader(GL_FRAGMENT_SHADER) {}
FragmentShader::FragmentShader(const char* source) : BasicShader(GL_FRAGMENT_SHADER, source) {}