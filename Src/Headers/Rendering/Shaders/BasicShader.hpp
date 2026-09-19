#pragma once
#include "Calculations/General/Types.hpp"
#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include "Utils/General/Logger.hpp"
template <u32 gl_shader_type>
class BasicShader {
private:
	boolean ready = false;
	std::string source = {};
	u32 gl_shader_id = {};
	void gen_shader() {
		gl_shader_id = glCreateShader(gl_shader_type);
	}
public:
	BasicShader(const BasicShader& other) = delete;
	BasicShader& operator=(const BasicShader& other) = delete;
	BasicShader() {
		gen_shader();
		ready = false;
	}
	BasicShader(const std::string& src) {
		gen_shader();
		source = src;
		ready = false;
	}
	~BasicShader() {
		if (gl_shader_id == 0) {
			return;
		}
		glDeleteShader(gl_shader_id);
	}
	void setSource(const std::string& src) {
		source = src;
		ready = false;
	}
	[[nodiscard]] boolean loadFromFile(const std::string& path) {
		ready = false;
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
		source = sourceacquired;
		return true;
	}
	[[nodiscard]] boolean compile() {
		ready = false;
		if (source.empty()) {
			return false;
		}
		const char* src = source.c_str();
		glShaderSource(gl_shader_id, 1, &src, NULL);
		glCompileShader(gl_shader_id);
		i32 success = 0;
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
	boolean readyToUse() const {
		return ready;
	}
	u32 getGlShaderId() const {
		return gl_shader_id;
	}
};