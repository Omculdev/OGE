#pragma once
#include "Rendering/Shaders/VertexShader.hpp"
#include "Rendering/Shaders/FragmentShader.hpp"
class ShaderProgram {
private:
	u32 gl_shader_program_id = {};
	void gen_program();
public:
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;
	ShaderProgram() = default;
	~ShaderProgram();
	void init();
	void create(VertexShader& vertexshader, FragmentShader& fragmentshader);
	void use() const;
	u32 getGlShaderProgramId() const;
};