#pragma once
#include "Calculations/General/Types.hpp"
#include "Calculations/General/Color.hpp"
#include "Graphics/2D/Drawable/Rectangle.hpp"
#include <GLFW/glfw3.h>
#include "Rendering/Window.hpp"
#include "Shaders/VertexShader.hpp"
#include "Shaders/FragmentShader.hpp"
#include "Shaders/ShaderProgram.hpp"
#include "VideoMemory/ElementBuffer.hpp"
#include "VideoMemory/VertexBuffer.hpp"
class Renderer {
private:
	VertexBuffer vertex_buffer = {};
	ElementBuffer element_buffer = {};
	VertexShader vertex_shader = {};
	FragmentShader fragment_shader = {};
	ShaderProgram shader_program = {};
	Window* current_window = {};
	f32 normalize_color(u8 color) const;
public:
	Renderer() = default;
	Renderer(Window* window);
	void bindWindow(Window* window);
	void clear(const Color& color);
	template<typename RectType>
	requires std::is_arithmetic_v<RectType>
	void draw(Rectangle<RectType>& rect);
};