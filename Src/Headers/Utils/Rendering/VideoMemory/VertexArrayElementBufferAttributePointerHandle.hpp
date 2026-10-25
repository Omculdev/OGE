#pragma once
#include "Utils/Rendering/VideoMemory/AttributePointerHandle.hpp"
#include <vector>
#include "Utils/Rendering/VideoMemory/VertexArrayElementBufferHandle.hpp"
class VertexArrayElementBufferAttributePointerHandle {
private:
	std::vector<AttributePointerHandle> attribute_pointer_handles = {};
	std::vector<usize> free_indeces = {};
	VertexArrayElementBufferHandle vertex_array_element_buffer_handle = {};
public:
	VertexArrayElementBufferAttributePointerHandle() = default;
	VertexArrayElementBufferAttributePointerHandle(const VertexArrayElementBufferAttributePointerHandle& other) = delete;
	VertexArrayElementBufferAttributePointerHandle& operator=(const VertexArrayElementBufferAttributePointerHandle& other) = delete;
	VertexArrayElementBufferAttributePointerHandle(VertexArrayElementBufferAttributePointerHandle&& other) noexcept;
	VertexArrayElementBufferAttributePointerHandle& operator=(VertexArrayElementBufferAttributePointerHandle&& other) noexcept;
	void addAttributePointerHandle(AttributePointerHandle&& attributepointerhandle);
	void deleteAttributePointerHandle(usize index);
	void setVertexArrayElementBufferHandleId(u32 id);
	void invalidateVertexArrayElementBufferHandle();
	[[nodiscard]] boolean isVertexArrayElementBufferHandleValid() const;
	[[nodiscard]] std::optional<u32> getVertexArrayElementBufferHandleId() const;
	[[nodiscard]] u32 getVertexArrayElementBufferHandleIdValue() const;
	[[nodiscard]] AttributePointerHandle& getAttributePointerHandle(usize index); 
	[[nodiscard]] std::vector<AttributePointerHandle>& getAllAttributePointerHandles();
};