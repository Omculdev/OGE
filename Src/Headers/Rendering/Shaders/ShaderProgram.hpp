#pragma once
#include "Rendering/Shaders/VertexShader.hpp"
#include "Rendering/Shaders/FragmentShader.hpp"
class ShaderProgram {
private:
	u32 gl_shader_program_id = {};
	void gen_program();
public:
	ShaderProgram() = default;
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;
	ShaderProgram(ShaderProgram&& other) noexcept;
	ShaderProgram& operator=(ShaderProgram&& other) noexcept;
	~ShaderProgram();
	void init();
	[[nodiscard]] boolean create(VertexShader& vertexshader, FragmentShader& fragmentshader);
	void reset();
	void use() const;
	u32 getGlShaderProgramId() const;
};