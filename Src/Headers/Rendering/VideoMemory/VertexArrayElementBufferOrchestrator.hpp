#pragma once
#include <vector>
#include "Rendering/VideoMemory/ElementBuffer.hpp"
#include "Rendering/VideoMemory/VertexArray.hpp"
#include "Utils/Rendering/VideoMemory/VertexArrayElementBufferAttributePointerHandle.hpp"
#include "Utils/Rendering/VideoMemory/AttributePointer.hpp"
#include <unordered_map>
class VertexArrayElementBufferOrchestrator {
private:
	struct VertexArrayElementBufferData {
		usize defragmentation_threshold = {};
		VertexArray vertex_array = {};
		ElementBuffer element_buffer = {};
	};
	std::vector<usize> free_indices = {};
	std::vector<VertexArrayElementBufferData> data = {};
	[[nodiscard]] VertexArrayElementBufferAttributePointerHandle init_members(
		u32 initialelementbufferusage,
		usize initialelementbuffersizebytes,
		usize initialelementbufferdefragmentationthresholdbytes,
		const std::vector<AttributePointer>& attributepointers
	);
public:
	VertexArrayElementBufferOrchestrator() = default;
	VertexArrayElementBufferOrchestrator(const VertexArrayElementBufferOrchestrator& other) = delete;
	VertexArrayElementBufferOrchestrator& operator=(const VertexArrayElementBufferOrchestrator& other) = delete;
	VertexArrayElementBufferOrchestrator(VertexArrayElementBufferOrchestrator&& other) noexcept;
	VertexArrayElementBufferOrchestrator& operator=(VertexArrayElementBufferOrchestrator&& other) noexcept;
	[[nodiscard]] VertexArrayElementBufferAttributePointerHandle init(
		usize initialelementbuffersizebytes = 1024 * 1024,
		usize initialelementbufferdefragmentationthresholdbytesu32 = 800 * 1024,
		u32 initialelementbufferusage = GL_DYNAMIC_DRAW,
		const std::vector<AttributePointer>& attributepointers = {}
	);
	[[nodiscard]] VertexArrayElementBufferAttributePointerHandle addVertexArrayElementBuffer(
		usize elementbuffersize = 1024 * 1024,
		usize elementbufferdefragmentationsize = 800 * 1024,
		u32 elementbufferusage = GL_DYNAMIC_DRAW,
		const std::vector<AttributePointer>& attributepointers = {}
	);
	template <typename IndexType>
	[[nodiscard]] std::optional<ElementBufferHandle> saveElementDataAndSendToGpu(
		const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		const std::vector<IndexType>& indeces,
		boolean active = true
	) {
		if (!vertexarrayelementbufferattributepointerhandle.isVertexArrayElementBufferHandleValid()) {
			Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::saveElementDataAndSendToGpu: attempted to send data to using an invalid handle");
			return std::nullopt;
		}
		ElementBufferHandle newelementbufferhandle;
		u32 id = vertexarrayelementbufferattributepointerhandle.vertex_array_element_buffer_handle.getIdValue();
		glBindVertexArray(data[id].vertex_array.getGlVertexArrayId());
		newelementbufferhandle = data[id].element_buffer.addElements(indeces, active);
		data[id].element_buffer.sendDataToGpu(newelementbufferhandle, GL_ELEMENT_ARRAY_BUFFER);
		glBindVertexArray(0);
		return newelementbufferhandle;
	}
	void deleteVertexArrayElementBuffer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle);
	void enableAllAttributePointers(const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle);
	void disableAllAttributePointers(const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle);
	void addAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, const AttributePointer& attributepointer);
	void addAttributePointer(
		VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		u32 layout,
		usize size,
		u32 type,
		boolean normalized,
		usize stride,
		usize shift,
		boolean enabled = true
	);
	void deleteAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, usize handleindex);
	void enableAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, usize handleindex);
	void disableAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, usize handleindex);
	void update();
};