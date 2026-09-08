#pragma once
#include "Calculations/General/Types.hpp"
#include "Calculations/General/Color.hpp"
#include <GLFW/glfw3.h>
#include "Rendering/Window.hpp"
class Renderer {
private:
	u32 vertex_buffer_object = 0;
	u32 element_buffer_object = 0;
	u32 vertex_array_object		= 0;
	Color clear_color = {};
	GLFWwindow* window = {};
	f32 normalize_color(u8 color) const;
	void generate_buffers();
	void generate_vertex_arrays();
public:
	Renderer();
	Renderer(const oge::Window& window);
	void bindWindow(const oge::Window& window);
	void clear(const Color& color);
};