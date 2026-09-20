#include <Rendering/Renderer.hpp>
#include <GLAD/glad.h>
void Renderer::bindWindow(Window* window) {
	current_window = window;
	glfwMakeContextCurrent(current_window->getPointer());
	if (window->depthEnabled()) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}
}
void Renderer::clear(const Color& color) const {
	glClearColor(color.r, color.g, color.b, color.a);
	if (current_window->depthEnabled()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
void Renderer::create_vertex_array() {
	vertex_array.addAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32) + 4 * sizeof(f32), 0);
	vertex_array.addAttributePointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 3 * sizeof(f32) + 4 * sizeof(f32), 3 * sizeof(f32));
	vertex_array.create(vertex_buffer, element_buffer, GL_DYNAMIC_DRAW);// change later
}
[[nodiscard]] boolean Renderer::load_shaders(const ShaderType& shadertype) {
	shader_type = shadertype;
	switch (shadertype) {
	case ShaderType::none:
		return false;
	case ShaderType::amount:
		return false;
	case ShaderType::no_rotate_2D:
		if (!vertex_shader.loadFromFile("Src/Shaders/NoRotate2DVertexShader.glsl")) {
			Logger::getInstance().logWarning("Renderer::load_shaders: failed to load vertex shader from: Src/Shaders/NoRotate2DVertexShader.glsl");
			return false;
		}
		if (!fragment_shader.loadFromFile("Src/Shaders/NoRotate2DFragmentShader.glsl")) {
			Logger::getInstance().logWarning("Renderer::load_shaders failed to load fragment shader from: Src/Shaders/NoRotate2DFragmentShader.glsl");
			return false;
		}
		return true;
	default:
		return false; // will add more shaders later
	}
}

void Renderer::load_shaders_and_create_shader_program() {
	if (!load_shaders(shader_type)) {
		Logger::getInstance().logWarning("Renderer::load_shaders_and_create_shader_program: failed to load one or multiple shaders");
	}
	shader_program.create(vertex_shader, fragment_shader);
}
void Renderer::setShaderType(const ShaderType& shadertype) {
	shader_type = shadertype;
}
void Renderer::init_all_rendering_parts() {
	vertex_array.init();
	vertex_buffer.init();
	element_buffer.init();
	vertex_shader.init();
	fragment_shader.init();
	shader_program.init();
}
void Renderer::init() {
	init_all_rendering_parts();
	vertex_buffer_defragmentation_threshold_bytes = 1024;
	element_buffer_defragmentation_threshold_bytes = 1024;
	shader_type = ShaderType::no_rotate_2D;
	load_shaders_and_create_shader_program();
	create_vertex_array();
}
void Renderer::init(Window* window) {
	init();
	glDisable(GL_DEPTH_TEST);
	current_window = window;
	glfwMakeContextCurrent(current_window->getPointer());
	if (window->depthEnabled()) {
		glEnable(GL_DEPTH_TEST);
	}
}
void Renderer::init(const ShaderType& shadertype) {
	init();
	shader_type = shadertype;
}
void Renderer::init(const ShaderType& shadertype, Window* window) {
	init(window);
	shader_type = shadertype;
}
void Renderer::update_vertex_buffer() {
	if (vertex_buffer.getBufferSize() - vertex_buffer.getUsedBufferSize() >= vertex_buffer_defragmentation_threshold_bytes) {
		vertex_buffer.defragmentBuffer();
	}
}
void Renderer::update_element_buffer() {
	if (element_buffer.getBufferSize() - element_buffer.getUsedBufferSize() >= element_buffer_defragmentation_threshold_bytes) {
		element_buffer.defragmentBuffer();
	}
}
void Renderer::update() {
	update_vertex_buffer();
	update_element_buffer();
}