#pragma once
#include "Calculations/General/Color.hpp"
#include "Graphics/2D/Drawable/Rectangle.hpp"
#include <GLFW/glfw3.h>
#include "Rendering/Window.hpp"
#include "Shaders/ShaderOrchestator.hpp"
#include "Rendering/VideoMemory/ResourceManager.hpp"
#include "VideoMemory/VertexArray.hpp"
#include "Rendering/DrawHandler.hpp"
class Renderer {
private:
	ShaderOrchestrator shader_orchestrator = {};
	ResourceManager resource_manager = {};
	DrawHandler draw_handler = {};
	Window* current_window = {};
	void init_members(const VertexBufferType& attributepointervertexbuffertype);
public:
	Renderer() = default;
	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer(Renderer&& other) noexcept;
	Renderer& operator=(Renderer&& other) noexcept;
	void init();
	void init(const VertexBufferType& attributepointervertexbuffertype);
	void init(Window* window);
	void init(Window* window, const VertexBufferType& attributepointervertexbuffertype);
	void bindWindow(Window* window);
	void clear(const Color& color) const;
	void update(); //defrag buffer
	template<typename RectangleType>
	requires std::is_arithmetic_v<RectangleType>
	void draw(
		Rectangle<RectangleType>& rectangle,
		const VertexBufferType& vertexbuffertype
	) {
		draw_handler.draw(
			resource_manager,
			resource_manager.getInitialVertexArrayElementBufferAttributePointerHandle(),
			rectangle,
			vertexbuffertype,
			shader_orchestrator
		);
	}
	template <typename RectangleType>
	requires std::is_arithmetic_v<RectangleType>
	void draw(
		Rectangle<RectangleType>& rectangle,
		VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		const VertexBufferType& vertexbuffertype
	) {
		draw_handler.draw(
			resource_manager,
			vertexarrayelementbufferattributepointerhandle,
			rectangle,
			vertexbuffertype,
			shader_orchestrator
		);
	}
};