#pragma once
#include "Rendering/Shaders/VertexShader.hpp"
#include "Rendering/Shaders/FragmentShader.hpp"
class ShaderProgram {
private:
	u32 gl_shader_program_id = {};
public:
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;
	ShaderProgram() = default;
	~ShaderProgram();
	void create(VertexShader& vertexshader, FragmentShader& fragmentshader);
	void use() const;
};