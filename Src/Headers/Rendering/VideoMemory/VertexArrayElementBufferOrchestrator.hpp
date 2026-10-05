#pragma once
#include <vector>
#include "Rendering/VideoMemory/ElementBuffer.hpp"
#include "Rendering/VideoMemory/VertexArray.hpp"
#include "Utils/Rendering/VideoMemory/VertexArrayElementBufferHandle.hpp"
#include "Utils/Rendering/VideoMemory/AttributePointer.hpp"
#include <unordered_map>
class VertexArrayElementBufferOrchestrator {
private:
	std::vector<boolean> disabled_ids;
	std::vector<usize> element_buffer_defragmentation_sizes = {};
	std::vector<VertexArray> vertex_arrays = {};
	std::vector<ElementBuffer> element_buffers = {};
	void init_initial_vertex_array();
	void init_initial_element_buffer(u32 initialelementbufferusage);
	void init_members(u32 initialelementbufferusage);
public:
	VertexArrayElementBufferOrchestrator() = default;
	VertexArrayElementBufferOrchestrator(const VertexArrayElementBufferOrchestrator& other) = delete;
	VertexArrayElementBufferOrchestrator& operator=(const VertexArrayElementBufferOrchestrator& other) = delete;
	VertexArrayElementBufferOrchestrator(VertexArrayElementBufferOrchestrator&& other) noexcept;
	VertexArrayElementBufferOrchestrator& operator=(VertexArrayElementBufferOrchestrator&& other) noexcept;
	void init(u32 initialelementbufferusage = GL_DYNAMIC_DRAW);
	[[nodiscard]] VertexArrayElementBufferHandle addVertexArrayElementBuffer(
		usize elementbuffersize = 1024 * 1024,
		usize elementbufferdefragmentationsize = 800 * 1024,
		u32 elementbufferusage = GL_DYNAMIC_DRAW,
		boolean vertexarrayenabled = true,
		const std::vector<AttributePointer>& attributepointers = {}
	);
	void deleteVertexArrayElementBuffer(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle);
	void enableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle);
	void disableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle);
	void update();
	[[nodiscard]] VertexArrayElementBufferHandle getInitialHandle() const;
};