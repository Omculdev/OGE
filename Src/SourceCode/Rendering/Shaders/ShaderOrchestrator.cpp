#include "Rendering/Shaders/ShaderOrchestator.hpp"
#include "Utils/General/Logger.hpp"
#include "Utils/Rendering/Shaders/ShaderLibrary.hpp"
void ShaderOrchestrator::init_members() {
	vertex_shader.init();
	fragment_shader.init();
	shader_program.init();
}
void ShaderOrchestrator::init() {
	init_members();
	shader_type = ShaderType::none;
}
void ShaderOrchestrator::init(const ShaderType& shadertype) {
	init_members();
	shader_type = shadertype;
}
[[nodiscard]] boolean ShaderOrchestrator::is_shader_type_valid(const ShaderType& shadertype) const {
	return !(shadertype == ShaderType::none || shadertype == ShaderType::amount);
}
[[nodiscard]] boolean ShaderOrchestrator::setShaderType(const ShaderType& shadertype) {
	if (!is_shader_type_valid(shadertype)) {
		Logger::getInstance().logWarning("ShaderOrchestrator::setShaderType: attempting to set shader type to an invalid type");
		return false;
	}
	shader_type = shadertype;
	return true;
}
[[nodiscard]] boolean ShaderOrchestrator::load_shaders(const ShaderType& shadertype) {
	auto shaderdescriptor = ShaderLibrary::getShaderPaths(shadertype);
	if (!shaderdescriptor.has_value()) {
		Logger::getInstance().logWarning("ShaderOrchestrator::load_single_shader: failed to get shader path for shader");
		return false;
	}
	if (!vertex_shader.loadFromFile(shaderdescriptor->vertex_shader_path)) {
		Logger::getInstance().logWarning("Renderer::load_shaders: failed to load vertex shader from: " + shaderdescriptor->vertex_shader_path);
		return false;
	}
	if (!fragment_shader.loadFromFile(shaderdescriptor->fragment_shader_path)) {
		Logger::getInstance().logWarning("Renderer::load_shaders failed to load fragment shader from: " + shaderdescriptor->fragment_shader_path);
		return false;
	}
	return true;
}
[[nodiscard]] boolean ShaderOrchestrator::loadCurrentShaderAndCreateShaderProgram() {
	if (!is_shader_type_valid(shader_type)) {
		Logger::getInstance().logWarning("ShaderOrchestrator::loadCurrentShaderAndCreateShaderProgram: attempting to load shaders and create program with an invalid shader type");
		return false;
	}
	vertex_shader.reset();
	fragment_shader.reset();
	shader_program.reset();
	boolean shadersloaded = load_shaders(shader_type);
	if (!shadersloaded) {
		return false;
	}
	return shader_program.create(vertex_shader, fragment_shader);
}
void ShaderOrchestrator::useShaderProgram() const {
	shader_program.use();
}