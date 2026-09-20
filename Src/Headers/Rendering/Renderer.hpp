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
#include "VideoMemory/VertexArray.hpp"
#include "Utils/Enums/ShaderTypes.hpp"
#include "Utils/Enums/Axes.hpp"
#include <array>
#include <unordered_map>
#include "Utils/VideoMemory/Mesh.hpp"
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
	VertexArray vertex_array = {};
	VertexBuffer vertex_buffer = {};
	ElementBuffer element_buffer = {};
	VertexShader vertex_shader = {};
	FragmentShader fragment_shader = {};
	ShaderProgram shader_program = {};
	ShaderType shader_type = {};
	Window* current_window = {};
	u32 vertex_offset = {};
	usize vertex_buffer_defragmentation_threshold_bytes = 0;
	usize element_buffer_defragmentation_threshold_bytes = 0;
	[[nodiscard]] boolean load_shaders(const ShaderType& shadertype);
	void create_vertex_array();
	void load_shaders_and_create_shader_program();
	template <usize vertexamount, usize indexamount>
	[[nodiscard]] Mesh saveVerticesAndIndeces(const std::array<Vertex, vertexamount>& vertices, const std::array<u32, indexamount>& indeces) {
		Mesh mesh;
		mesh.vertex_buffer_handle = vertex_buffer.addElements(vertexamount * sizeof(Vertex), vertices.data());
		mesh.element_buffer_handle = element_buffer.addElements(indexamount * sizeof(u32), indeces.data());
		return mesh;
	}
	void sendLastAcquiredDataToGpu() {
		glBindVertexArray(vertex_array.getGlVertexArrayId());
		vertex_buffer.sendDataToGpu(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
		element_buffer.sendDataToGpu(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
	}
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
	void init_all_rendering_parts();
	void update_vertex_buffer();
	void update_element_buffer();
public:
	Renderer() = default;
	void init();
	void init(const ShaderType& shadertype);
	void init(Window* window);
	void init(const ShaderType& shadertype, Window* window);
	void bindWindow(Window* window);
	void clear(const Color& color) const;
	void update(); //defrag buffer
	void setShaderType(const ShaderType& shadertype);
	template<typename RectType>
	requires std::is_arithmetic_v<RectType>
	void draw(const Rectangle<RectType>& rectangle) {
		auto it = gpu_objects.find(rectangle.getId());
		if (it == gpu_objects.end()) {
			saveRectangleDataAndSendToGpu(rectangle);
			it = gpu_objects.find(rectangle.getId());
		}
		shader_program.use();
		glBindVertexArray(vertex_array.getGlVertexArrayId());
		glDrawElements(
			GL_TRIANGLES,
			it->second.element_buffer_data.element_buffer_size_bytes/sizeof(u32), // identical for each rect
			GL_UNSIGNED_INT,
			reinterpret_cast<void*>(it->second.element_buffer_data.element_buffer_offset_bytes)
		); 
	}
};