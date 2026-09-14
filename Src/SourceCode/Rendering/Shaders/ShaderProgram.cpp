#include "Rendering/Shaders/ShaderProgram.hpp"
#include "GLAD/glad.h"
#include "Utils/General/Logger.hpp"
void ShaderProgram::create(VertexShader& vertexshader, FragmentShader& fragmentshader) {
	gl_shader_program_id = glCreateProgram();
	vertexshader.compile();
	fragmentshader.compile();
	glAttachShader(gl_shader_program_id, vertexshader.getGlShaderId());
	glAttachShader(gl_shader_program_id, fragmentshader.getGlShaderId());
	glLinkProgram(gl_shader_program_id);
	i32 success = 0;
	glGetProgramiv(gl_shader_program_id, GL_LINK_STATUS, &success);
	if (!success) {
		char logdata[1024];
		glGetProgramInfoLog(gl_shader_program_id, sizeof(logdata), NULL, logdata);
		Logger::getInstance().logWarning("ShaderProgram::ShaderProgram: failed to link shader program: " + std::string(logdata));
		glDeleteProgram(gl_shader_program_id);
		gl_shader_program_id = 0;
		return;
	}
	glDetachShader(gl_shader_program_id, vertexshader.getGlShaderId());
	glDetachShader(gl_shader_program_id, fragmentshader.getGlShaderId());
}
ShaderProgram::~ShaderProgram() {
	glDeleteProgram(gl_shader_program_id);
}
void ShaderProgram::use() const {
	glUseProgram(gl_shader_program_id);
}