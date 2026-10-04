#pragma once
#include "Calculations/General/Types.hpp"
#include "Calculations/General/Color.hpp"
#include "Graphics/2D/Drawable/Rectangle.hpp"
#include <GLFW/glfw3.h>
#include "Rendering/Window.hpp"
#include "Shaders/ShaderOrchestator.hpp"
#include "Rendering/VideoMemory/BufferOrchestrator.hpp"
#include "VideoMemory/VertexArray.hpp"
#include "Utils/Enums/Axes.hpp"
#include <array>
#include <unordered_map>
#include <iostream>
class Renderer {
public:
	struct GpuObject {
		struct ElementBufferData {
			usize element_buffer_offset_bytes = {};
			usize element_buffer_size_bytes = {};
		};
		ElementBufferData element_buffer_data;
		Mesh mesh;
	};
	std::unordered_map<u32, GpuObject> gpu_objects = {};
	BufferOrchestrator buffer_orchestrator = {};
	ShaderOrchestrator shader_orchestrator = {};
	VertexArray vertex_array = {};
	Window* current_window = {};
	u32 vertex_offset = {};
	void create_vertex_array(u32 usage);
	template<typename RectType>
	requires std::is_arithmetic_v<RectType>
	void saveRectangleDataAndSendToGpu(const Rectangle<RectType>& rectangle) {
		usize rectanglevertexamount = static_cast<usize>(RectangleVertex::amount);
		Mesh meshacquired = saveVerticesAndIndeces<static_cast<usize>(RectangleVertex::amount), 6>(
			rectangle.getFullVertexData(),
			{
				0 + vertex_offset,
				1 + vertex_offset,
				3 + vertex_offset,
				0 + vertex_offset,
				2 + vertex_offset,
				3 + vertex_offset
			} //identical for each rectangle
		);
		vertex_offset += static_cast<usize>(RectangleVertex::amount);
		GpuObject::ElementBufferData newelementbufferdata;
		newelementbufferdata.element_buffer_size_bytes = 6 * sizeof(u32); // idential for each rectangle
		newelementbufferdata.element_buffer_offset_bytes = element_buffer.getOffset(meshacquired.element_buffer_handle);
		sendLastAcquiredDataToGpu();
		gpu_objects[rectangle.getId()] = { newelementbufferdata, meshacquired };

	}
	void init_members();
	void update_vertex_buffer();
	void update_element_buffer();
public:
	Renderer() = default;
	void init();
	void init(Window* window);
	void bindWindow(Window* window);
	void clear(const Color& color) const;
	void update(); //defrag buffer
	template<typename RectType>
	requires std::is_arithmetic_v<RectType>
	void draw(const Rectangle<RectType>& rectangle) {
		auto it = gpu_objects.find(rectangle.getId());
		if (it == gpu_objects.end()) {
			saveRectangleDataAndSendToGpu(rectangle);
			it = gpu_objects.find(rectangle.getId());
		}
		shader_orchestrator.useShaderProgram();
		glBindVertexArray(vertex_array.getGlVertexArrayId());
		glDrawElements(
			GL_TRIANGLES,
			it->second.element_buffer_data.element_buffer_size_bytes/sizeof(u32), // identical for each rect
			GL_UNSIGNED_INT,
			reinterpret_cast<void*>(it->second.element_buffer_data.element_buffer_offset_bytes)
		); 
	}
};