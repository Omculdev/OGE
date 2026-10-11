#pragma once
#include "Utils/Rendering/VideoMemory/ElementBufferHandle.hpp"
#include "Utils/Rendering/VideoMemory/VertexBufferHandle.hpp"
class ResourceHandle {
private:
	VertexBufferHandle vertex_buffer_handle = {};
	ElementBufferHandle element_buffer_handle = {};
public:
	ResourceHandle() = default;
	ResourceHandle(const ResourceHandle& other) = delete;
	ResourceHandle& operator=(const ResourceHandle& other) = delete;
	ResourceHandle(ResourceHandle&& other) noexcept;
	ResourceHandle& operator=(ResourceHandle&& other) noexcept;
	void setVertexBufferHandle(VertexBufferHandle&& vertexbufferhandle);
	void setElementBufferHandle(ElementBufferHandle&& elementbufferhandle);
	VertexBufferHandle& getVertexBufferHandle();
	ElementBufferHandle& getElementBufferHandle();
};
