#include <Rendering/Renderer.hpp>
#include <GLAD/glad.h>
f32 Renderer::normalize_color(u8 color) const {
	return static_cast<f32>(color) / static_cast<f32>(255);
}
Renderer::Renderer(const oge::Window& window ) {
	this->window = window;
}
void Renderer::clear(const Color& color) {

}
void Renderer::generate_buffers() {
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}
void Renderer::generate_vertex_arrays() {
	glGenVertexArrays(1, &VAO);
}