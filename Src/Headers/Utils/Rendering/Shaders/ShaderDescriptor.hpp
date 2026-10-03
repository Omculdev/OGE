#pragma once
#include <string>
class ShaderDescriptor {
public:
	ShaderDescriptor() = default;
	ShaderDescriptor(const std::string& vertexshaderpath, const std::string& fragmentshaderpath) :
		vertex_shader_path(vertexshaderpath),
		fragment_shader_path(fragmentshaderpath) {}
	std::string vertex_shader_path = {};
	std::string fragment_shader_path = {};
};
