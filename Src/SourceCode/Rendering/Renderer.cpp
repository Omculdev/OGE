#include <Rendering/Renderer.hpp>
#include <GLAD/glad.h>
Renderer::Renderer(Renderer&& other) noexcept :
	shader_orchestrator(std::move(other.shader_orchestrator)),
	resource_manager(std::move(other.resource_manager)),
	draw_handler(std::move(other.draw_handler)),
	current_window(other.current_window)
{
	other.current_window = nullptr;
}
Renderer& Renderer::operator=(Renderer&& other) noexcept {
	if (this == &other) return *this;
	shader_orchestrator = std::move(other.shader_orchestrator);
	resource_manager = std::move(other.resource_manager);
	draw_handler = std::move(other.draw_handler);
	current_window = other.current_window;
	other.current_window = nullptr;
	return *this;
}
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
void Renderer::init_members(const VertexBufferType& attributepointervertexbuffertype) {
	resource_manager.init();
	// change later - placeholder
	resource_manager.vertex_array_element_buffer_orchestrator.addAttributePointer(
		resource_manager.getInitialVertexArrayElementBufferAttributePointerHandle(),
		resource_manager.vertex_buffer_orchestrator, attributepointervertexbuffertype,
		0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), 0, true 
	);
	resource_manager.vertex_array_element_buffer_orchestrator.addAttributePointer(
		resource_manager.getInitialVertexArrayElementBufferAttributePointerHandle(),
		resource_manager.vertex_buffer_orchestrator, attributepointervertexbuffertype,
		1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), 3 * sizeof(f32), true
	);
	// change later - placeholder
	shader_orchestrator.init();
}
void Renderer::init(const VertexBufferType& attributepointervertexbuffertype) {
	init_members(attributepointervertexbuffertype);
	shader_orchestrator.setShaderType(ShaderType::no_rotate_2D);  // remove later
	if (!shader_orchestrator.loadCurrentShaderAndCreateShaderProgram()) {
		Logger::getInstance().logWarning("Renderer::init: failed to link shader program");
		return;
	}
}
void Renderer::init() {
	init(VertexBufferType::dynamical);
}
void Renderer::init(Window* window) {
	init();
	bindWindow(window);
}
void Renderer::init(Window* window, const VertexBufferType& attributepointervertexbuffertype) {
	init(attributepointervertexbuffertype);
	bindWindow(window);
}
void Renderer::update() {
	resource_manager.update();
}