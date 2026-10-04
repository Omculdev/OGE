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
void Renderer::create_vertex_array(u32 usage) {
	vertex_array.addAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32) + 4 * sizeof(f32), 0);
	vertex_array.addAttributePointer(1, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(f32) + 4 * sizeof(f32), 3 * sizeof(f32));
	vertex_array.create(vertex_buffer, element_buffer, usage);// change later
}
void Renderer::init_members() {
	vertex_array.init();
	buffer_orchestrator.init();
	shader_orchestrator.init();
}
void Renderer::init() {
	init_members();
	vertex_buffer_defragmentation_threshold_bytes = 1024;
	element_buffer_defragmentation_threshold_bytes = 1024;
	shader_orchestrator.setShaderType(ShaderType::no_rotate_2D);  // remove later
	if (!shader_orchestrator.loadCurrentShaderAndCreateShaderProgram()) {
		Logger::getInstance().logWarning("Renderer::init: failed to link shader program");
		return;
	}
	create_vertex_array(GL_DYNAMIC_DRAW);
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
void Renderer::update() {
	buffer_orchestrator.updateBuffers();
}