#pragma once
#include "Utils/Rendering/VideoMemory/ElementBufferHandle.hpp"
#include "Utils/Rendering/VideoMemory/VertexBufferHandle.hpp"
#include "Utils/Enums/VertexBufferTypes.hpp"
class ResourceHandle {
private:
	VertexBufferHandle vertex_buffer_handle = {};
	ElementBufferHandle element_buffer_handle = {};
	VertexBufferType vertex_buffer_type = {};
	u32 gl_vertex_array_id = {}; // raw gl id not owned
	u32 index_count = {};
	i32 index_type = {};
	boolean shared_element_buffer = {};
public:
	ResourceHandle() = default;
	ResourceHandle(const ResourceHandle& other) = delete;
	ResourceHandle& operator=(const ResourceHandle& other) = delete;
	ResourceHandle(ResourceHandle&& other) noexcept;
	ResourceHandle& operator=(ResourceHandle&& other) noexcept;
	void setGlVertexArrayId(u32 id);
	void setUsesSharedElementBuffer();
	void setDoesntUseSharedElementBuffer();
	void setVertexBufferHandle(VertexBufferHandle&& vertexbufferhandle);
	void setElementBufferHandle(ElementBufferHandle&& elementbufferhandle);
	void setVertexBufferType(const VertexBufferType& vertexbuffertype);
	void setIndexCount(u32 count);
	void setIndexType(i32 type);
	[[nodiscard]] u32 getIndexCount() const;
	[[nodiscard]] i32 getIndexType() const;
	[[nodiscard]] u32 getGlVertexArrayId() const;
	[[nodiscard]] boolean getUsesSharedElementBuffer() const; 
	[[nodiscard]] const VertexBufferType& getVertexBufferType() const;
	[[nodiscard]] const VertexBufferHandle& getVertexBufferHandle() const;
	[[nodiscard]] const ElementBufferHandle& getElementBufferHandle() const;
	[[nodiscard]] VertexBufferType& getVertexBufferType();
	[[nodiscard]] VertexBufferHandle& getVertexBufferHandle();
	[[nodiscard]] ElementBufferHandle& getElementBufferHandle();
	void invalidate();
};
