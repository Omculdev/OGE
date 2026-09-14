#include <Rendering/Renderer.hpp>
#include <GLAD/glad.h>
Renderer::Renderer(Window* window ) {
	glDisable(GL_DEPTH_TEST);
	current_window = window;
	glfwMakeContextCurrent(current_window->getPointer());
	if (window->depthEnabled()) {
		glEnable(GL_DEPTH_TEST);
	}
}
f32 Renderer::normalize_color(u8 color) const {
	return static_cast<f32>(color) / static_cast<f32>(255);
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
void Renderer::clear(const Color& color) {
	glClearColor(color.r, color.g, color.b, color.a);
	if (current_window->depthEnabled()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT);
	}
}


