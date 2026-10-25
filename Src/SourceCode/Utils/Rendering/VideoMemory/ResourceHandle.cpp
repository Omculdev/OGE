#include "Utils/Rendering/VideoMemory/ResourceHandle.hpp"
#include <utility>
ResourceHandle::ResourceHandle(ResourceHandle&& other) noexcept :
	vertex_buffer_handle(std::move(other.vertex_buffer_handle)),
	element_buffer_handle(std::move(other.element_buffer_handle)),
	vertex_buffer_type(other.vertex_buffer_type),
	gl_vertex_array_id(other.gl_vertex_array_id),
	index_count(other.index_count),
	index_type(other.index_type),
	shared_element_buffer(other.shared_element_buffer)
{
	other.vertex_buffer_type = VertexBufferType::none;
	other.gl_vertex_array_id = 0;
	other.index_count = 0;
	other.index_type = 0;
	other.shared_element_buffer = false;
}
ResourceHandle& ResourceHandle::operator=(ResourceHandle&& other) noexcept {
	if (this == &other) return *this;
	vertex_buffer_handle = std::move(other.vertex_buffer_handle);
	element_buffer_handle = std::move(other.element_buffer_handle);
	vertex_buffer_type = other.vertex_buffer_type;
	gl_vertex_array_id = other.gl_vertex_array_id;
	index_count = other.index_count;
	index_type = other.index_type;
	shared_element_buffer = other.shared_element_buffer;
	other.vertex_buffer_type = VertexBufferType::none;
	other.gl_vertex_array_id = 0;
	other.index_count = 0;
	other.index_type = 0;
	other.shared_element_buffer = false;
	return *this;
}
void ResourceHandle::setVertexBufferHandle(VertexBufferHandle&& vertexbufferhandle) {
	vertex_buffer_handle = std::move(vertexbufferhandle);
}
void ResourceHandle::setElementBufferHandle(ElementBufferHandle&& elementbufferhandle) {
	element_buffer_handle = std::move(elementbufferhandle);
}
void ResourceHandle::setVertexBufferType(const VertexBufferType& vertexbuffertype) {
	vertex_buffer_type = vertexbuffertype;
}
const VertexBufferHandle& ResourceHandle::getVertexBufferHandle() const {
	return vertex_buffer_handle;
}
const ElementBufferHandle& ResourceHandle::getElementBufferHandle() const {
	return element_buffer_handle;
}
const VertexBufferType& ResourceHandle::getVertexBufferType() const {
	return vertex_buffer_type;
}
 VertexBufferHandle& ResourceHandle::getVertexBufferHandle()  {
	return vertex_buffer_handle;
}
 ElementBufferHandle& ResourceHandle::getElementBufferHandle()  {
	return element_buffer_handle;
}
 VertexBufferType& ResourceHandle::getVertexBufferType()  {
	return vertex_buffer_type;
}
 void ResourceHandle::invalidate() {
	 vertex_buffer_handle.invalidate();
	 element_buffer_handle.invalidate();
	 vertex_buffer_type = VertexBufferType::none;
 }
 void ResourceHandle::setUsesSharedElementBuffer() {
	 shared_element_buffer = true;
 }
 void ResourceHandle::setDoesntUseSharedElementBuffer() {
	 shared_element_buffer = false;
 }
 [[nodiscard]] boolean ResourceHandle::getUsesSharedElementBuffer() const {
	 return shared_element_buffer;
 }
 void ResourceHandle::setGlVertexArrayId(u32 id) {
	 gl_vertex_array_id = id;
 }
 [[nodiscard]] u32 ResourceHandle::getGlVertexArrayId() const {
	 return gl_vertex_array_id;
 }
 void ResourceHandle::setIndexCount(u32 count) {
	 index_count = count;
 }
 [[nodiscard]] u32 ResourceHandle::getIndexCount() const {
	 return index_count;
 }
 void ResourceHandle::setIndexType(i32 type) {
	 index_type = type;
 }
 [[nodiscard]] i32 ResourceHandle::getIndexType() const {
	 return index_type;
 }