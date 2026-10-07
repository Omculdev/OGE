#include "Rendering/VideoMemory/VertexArray.hpp"
#include <Calculations/General/Types.hpp>
#include <GLAD/glad.h>
#include <Rendering/VideoMemory/ElementBuffer.hpp>
#include <Rendering/VideoMemory/VertexBuffer.hpp>
#include <utility>
VertexArray::VertexArray(VertexArray&& other) noexcept :
	gl_vertex_array_id(other.gl_vertex_array_id),
	attribute_pointers(std::move(other.attribute_pointers)),
	free_indeces(std::move(other.free_indeces))
{
	other.gl_vertex_array_id = 0;
}
VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
	if (this == &other) return *this;
	if (gl_vertex_array_id != 0) {
		glDeleteVertexArrays(1, &gl_vertex_array_id);
	}
	gl_vertex_array_id = other.gl_vertex_array_id;
	attribute_pointers = std::move(other.attribute_pointers);
	free_indeces = std::move(other.free_indeces);
	other.gl_vertex_array_id = 0;
	return *this;
}
void VertexArray::gen_array() {
	glGenVertexArrays(1, &gl_vertex_array_id);
}
void VertexArray::init() {
	gen_array();
}
VertexArray::~VertexArray() {
	if (gl_vertex_array_id != 0) {
		glDeleteVertexArrays(1, &gl_vertex_array_id);
	}
}
[[nodiscard]] AttributePointerHandle VertexArray::addAttributePointer(const AttributePointer& attributepointer) {
	AttributePointerHandle attributepointerhandle;
	if (free_indeces.empty()) {
		attributepointerhandle.setId(attribute_pointers.size()); // implicitly last index + 1
		attribute_pointers.push_back(std::move(attributepointer));
	}
	else {
		usize freeindex = free_indeces.back();
		free_indeces.pop_back();
		attributepointerhandle.setId(freeindex);
		attribute_pointers[freeindex] = std::move(attributepointer);
	}
	glBindVertexArray(gl_vertex_array_id);
	glVertexAttribPointer(
		attributepointer.layout,
		attributepointer.size, 
		attributepointer.type,
		attributepointer.normalized, 
		attributepointer.stride,
		reinterpret_cast<void*>(attributepointer.shift)
	);
	if (attributepointer.enabled) {
		glEnableVertexAttribArray(attributepointer.layout);
	}
	else {
		glDisableVertexAttribArray(attributepointer.layout);
	}
	glBindVertexArray(0);
	return attributepointerhandle;
}
[[nodiscard]] AttributePointerHandle VertexArray::addAttributePointer(
	u32 layout,
	usize size, 
	u32 type, 
	boolean normalized, 
	usize stride, 
	usize shift,
	boolean enabled
) {
	AttributePointer newattributepointer;
	newattributepointer.layout = layout;
	newattributepointer.size = size;
	newattributepointer.type = type;
	newattributepointer.normalized = normalized;
	newattributepointer.stride = stride;
	newattributepointer.shift = shift;
	newattributepointer.enabled = enabled;
	return addAttributePointer(newattributepointer);
}
void VertexArray::enableAllAttributePointers() {
	glBindVertexArray(gl_vertex_array_id);
	for (auto& attributepointer : attribute_pointers) {
		glEnableVertexAttribArray(attributepointer.layout);
	}
	glBindVertexArray(0);
}
void VertexArray::disableAllAttributePointers() {
	glBindVertexArray(gl_vertex_array_id);
	for (auto& attributepointer : attribute_pointers) {
		glDisableVertexAttribArray(attributepointer.layout);
	}
	glBindVertexArray(0);
}
void VertexArray::enableAttributePointer(AttributePointerHandle attributepointerhandle) {
	if (!attributepointerhandle.isValid()) {
		Logger::getInstance().logWarning("VertexArray::enableAttributePointer: attempted to data via an invalid handle");
		return;
	}
	attribute_pointers[attributepointerhandle.getIdValue()].enabled = true;
	glBindVertexArray(gl_vertex_array_id);
	glEnableVertexAttribArray(attribute_pointers[attributepointerhandle.getIdValue()].layout);
	glBindVertexArray(0);
}
void VertexArray::disableAttributePointer(const AttributePointerHandle& attributepointerhandle) {
	if (!attributepointerhandle.isValid()) {
		Logger::getInstance().logWarning("VertexArray::disableAttributePointer: attempted to data via an invalid handle");
		return;
	}
	attribute_pointers[attributepointerhandle.getIdValue()].enabled = false;
	glBindVertexArray(gl_vertex_array_id);
	glDisableVertexAttribArray(attribute_pointers[attributepointerhandle.getIdValue()].layout);
	glBindVertexArray(0);
}
void VertexArray::clear() {
	if (gl_vertex_array_id != 0) {
		glDeleteVertexArrays(1, &gl_vertex_array_id);
		gl_vertex_array_id = 0;
	}
	attribute_pointers.clear();
	free_indeces.clear();
}
u32 VertexArray::getGlVertexArrayId() const {
	return gl_vertex_array_id;
}