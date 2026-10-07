#pragma once
#include <vector>
#include "Rendering/VideoMemory/ElementBuffer.hpp"
#include "Rendering/VideoMemory/VertexArray.hpp"
#include "Utils/Rendering/VideoMemory/VertexArrayElementBufferHandle.hpp"
#include "Utils/Rendering/VideoMemory/AttributePointer.hpp"
#include <unordered_map>
class VertexArrayElementBufferOrchestrator {
private:
	struct VertexArrayElementBufferData {
		boolean enabled = {};
		usize defragmentation_threshold = {};
		VertexArray vertex_array = {};
		ElementBuffer element_buffer = {};
	};
	std::vector<usize> free_indices = {};
	std::vector<VertexArrayElementBufferData> data = {};
	void init_members(u32 initialelementbufferusage);
	// rework for usage with new attrib pointers
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
	template <typename IndexType>
	[[nodiscard]] std::optional<ElementBufferHandle> saveElementDataAndSendToGpu(
		const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle,
		const std::vector<IndexType>& indeces,
		boolean active = true
	) {
		if (!vertexarrayelementbufferhandle.isValid()) {
			Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::saveElementDataAndSendToGpu: attempted to send data to using an invalid handle");
			return std::nullopt;
		}
		ElementBufferHandle newelementbufferhandle;
		glBindVertexArray(data[vertexarrayelementbufferhandle.getIdValue()].vertex_array.getGlVertexArrayId());
		newelementbufferhandle = data[vertexarrayelementbufferhandle.getIdValue()].element_buffer.addElements(indeces, active);
		data[vertexarrayelementbufferhandle.getIdValue()].element_buffer.sendDataToGpu(newelementbufferhandle, GL_ELEMENT_ARRAY_BUFFER);
		glBindVertexArray(0);
		return newelementbufferhandle;
	}
	void deleteVertexArrayElementBuffer(VertexArrayElementBufferHandle& vertexarrayelementbufferhandle);
	void enableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle);
	void disableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle);
	void addAttributePointer(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle, const AttributePointer& attributepointer);
	void deleteAttributePointer(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle);
	void update();
	[[nodiscard]] VertexArrayElementBufferHandle getInitialHandle() const;
};