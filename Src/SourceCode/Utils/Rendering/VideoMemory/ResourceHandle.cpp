#include "Utils/Rendering/VideoMemory/ResourceHandle.hpp"
#include <utility>
ResourceHandle::ResourceHandle(ResourceHandle&& other) noexcept :
	vertex_buffer_handle(std::move(other.vertex_buffer_handle)),
	element_buffer_handle(std::move(other.element_buffer_handle))
{}
ResourceHandle& ResourceHandle::operator=(ResourceHandle&& other) noexcept {
	if (this == &other) return *this;
	vertex_buffer_handle = std::move(other.vertex_buffer_handle);
	element_buffer_handle = std::move(other.element_buffer_handle);
	return *this;
}
void ResourceHandle::setVertexBufferHandle(VertexBufferHandle&& vertexbufferhandle) {
	vertexbufferhandle = std::move(vertexbufferhandle);
}
void ResourceHandle::setElementBufferHandle(ElementBufferHandle&& elementbufferhandle) {
	element_buffer_handle = std::move(elementbufferhandle);
}
VertexBufferHandle& ResourceHandle::getVertexBufferHandle() {
	return vertex_buffer_handle;
}
ElementBufferHandle& ResourceHandle::getElementBufferHandle() {
	return element_buffer_handle;
}