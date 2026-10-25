#include "Utils/Rendering/VideoMemory/VertexArrayElementBufferAttributePointerHandle.hpp"
#include "Utils/General/Logger.hpp"
VertexArrayElementBufferAttributePointerHandle::VertexArrayElementBufferAttributePointerHandle(VertexArrayElementBufferAttributePointerHandle&& other) noexcept :
	attribute_pointer_handles(std::move(other.attribute_pointer_handles)),
	free_indeces(std::move(other.free_indeces)),
	vertex_array_element_buffer_handle(std::move(other.vertex_array_element_buffer_handle))
{}
VertexArrayElementBufferAttributePointerHandle& VertexArrayElementBufferAttributePointerHandle::operator=(VertexArrayElementBufferAttributePointerHandle&& other) noexcept {
	if (&other == this) return *this;
	attribute_pointer_handles = std::move(other.attribute_pointer_handles);
	free_indeces = std::move(other.free_indeces);
	vertex_array_element_buffer_handle = std::move(other.vertex_array_element_buffer_handle);
	return *this;
}
void VertexArrayElementBufferAttributePointerHandle::addAttributePointerHandle(AttributePointerHandle&& attributepointerhandle) {
	if (!attributepointerhandle.isValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferAttributePointerHandle::addAttributePointerHandle attempted to add an invalid attribute pointer handle");
		return;
	}
	attribute_pointer_handles.push_back(std::move(attributepointerhandle));
}
void VertexArrayElementBufferAttributePointerHandle::deleteAttributePointerHandle(usize index) {
	attribute_pointer_handles[index].invalidate();
	free_indeces.push_back(index);
}
void VertexArrayElementBufferAttributePointerHandle::setVertexArrayElementBufferHandleId(u32 id) {
	vertex_array_element_buffer_handle.setId(id);
}
void VertexArrayElementBufferAttributePointerHandle::invalidateVertexArrayElementBufferHandle() {
	vertex_array_element_buffer_handle.invalidate();
}
[[nodiscard]] boolean VertexArrayElementBufferAttributePointerHandle::isVertexArrayElementBufferHandleValid() const {
	return vertex_array_element_buffer_handle.isValid();
}
[[nodiscard]] std::optional<u32> VertexArrayElementBufferAttributePointerHandle::getVertexArrayElementBufferHandleId() const {
	return vertex_array_element_buffer_handle.getId();
}
[[nodiscard]] u32 VertexArrayElementBufferAttributePointerHandle::getVertexArrayElementBufferHandleIdValue() const {
	return vertex_array_element_buffer_handle.getIdValue();
}
[[nodiscard]] AttributePointerHandle& VertexArrayElementBufferAttributePointerHandle::getAttributePointerHandle(usize index) {
	return attribute_pointer_handles[index];
}
[[nodiscard]] std::vector<AttributePointerHandle>& VertexArrayElementBufferAttributePointerHandle::getAllAttributePointerHandles() {
	return attribute_pointer_handles;
}