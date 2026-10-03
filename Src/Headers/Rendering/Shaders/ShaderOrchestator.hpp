#pragma once
#include "Rendering/Shaders/VertexShader.hpp"
#include "Rendering/Shaders/FragmentShader.hpp"
#include "Rendering/Shaders/ShaderProgram.hpp"
#include "Utils/Enums/ShaderTypes.hpp"
class ShaderOrchestrator {
private:
	VertexShader vertex_shader = {};
	FragmentShader fragment_shader = {};
	ShaderProgram shader_program = {};
	ShaderType shader_type = {};
	void init_members();
	[[nodiscard]] boolean is_shader_type_valid(const ShaderType& shadertype) const;
	[[nodiscard]] boolean load_shaders(const ShaderType& shadertype);
public:
	ShaderOrchestrator() = default;
	ShaderOrchestrator(const ShaderOrchestrator& other) = delete;
	ShaderOrchestrator& operator=(const ShaderOrchestrator& other) = delete;
	void init();
	void init(const ShaderType& shadertype);
	[[nodiscard]] boolean setShaderType(const ShaderType& shadertype);
	[[nodiscard]] boolean loadCurrentShaderAndCreateShaderProgram();
	void useShaderProgram() const;
};