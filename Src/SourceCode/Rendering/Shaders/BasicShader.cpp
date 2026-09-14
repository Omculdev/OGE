#include "Rendering/Shaders/BasicShader.hpp"
#include "Utils/General/Logger.hpp"
#include <fstream>
void BasicShader::gen_shader() {
	gl_shader_id = glCreateShader(gl_shader_type);
}
BasicShader::BasicShader(u32 type) {
	gl_shader_type = type;
	gen_shader();
}
BasicShader::BasicShader(u32 type, const std::string& src) {
	gl_shader_type = type;
	gen_shader();
	source = src.c_str();
}
BasicShader::~BasicShader() {
	if (gl_shader_id == 0) {
		return;
	}
	glDeleteShader(gl_shader_id);
	gl_shader_id = 0;
}
void BasicShader::setSource(const std::string& src) {
	source = src.c_str();
}
[[nodiscard]] bool BasicShader::loadFromFile(const std::string& path) {
	std::ifstream inputfile(path);
	if (!inputfile.is_open()) {
		return false;
	}
	std::string sourceacquired = "";
	std::string sourcestring = "";
	while (std::getline(inputfile, sourcestring)) {
		sourceacquired += sourcestring;
		sourceacquired += '\n';
	}
	source = sourceacquired.c_str();
	return true;
}
[[nodiscard]] bool BasicShader::compile() {
	ready = false;
	if (source == nullptr) {
		return false;
	}
	glShaderSource(gl_shader_id, 1, &source, NULL);
	glCompileShader(gl_shader_id);
	i32 success;
	glGetShaderiv(gl_shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		char logdata[1024];
		glGetShaderInfoLog(gl_shader_id, sizeof(logdata), NULL, logdata);
		Logger::getInstance().logWarning("BasicShader::compile: shader compilation failed" + std::string(logdata));
		return false;
	}
	ready = true;
	return true;
}
bool BasicShader::readyToUse() const { 
	return ready;
}
u32 BasicShader::getGlShaderId() const {
	return gl_shader_id;
}