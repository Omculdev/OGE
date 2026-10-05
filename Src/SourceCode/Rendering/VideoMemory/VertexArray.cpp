#include "Rendering/VideoMemory/VertexArray.hpp"
#include <Calculations/General/Types.hpp>
#include <GLAD/glad.h>
#include <Rendering/VideoMemory/ElementBuffer.hpp>
#include <Rendering/VideoMemory/VertexBuffer.hpp>
#include <utility>
VertexArray::VertexArray(VertexArray&& other) noexcept :
	gl_vertex_array_id(other.gl_vertex_array_id),
	attribute_pointers(std::move(other.attribute_pointers)) 
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
void VertexArray::addAttributePointer(const AttributePointer& attributepointer) {
	attribute_pointers.push_back(std::move(attributepointer));
}
void VertexArray::addAttributePointer(u32 layout, usize size, u32 type, boolean normalized, usize stride, usize shift) {
	AttributePointer newattribpointer;
	newattribpointer.layout = layout;
	newattribpointer.size = size;
	newattribpointer.type = type;
	newattribpointer.normalized = normalized;
	newattribpointer.stride = stride;
	newattribpointer.shift = shift;
	glBindVertexArray(gl_vertex_array_id);
	glVertexAttribPointer(newattribpointer.layout, newattribpointer.size, newattribpointer.type, newattribpointer.normalized, newattribpointer.stride, reinterpret_cast<void*>(newattribpointer.shift));
	glBindVertexArray(0);
	attribute_pointers.push_back(std::move(newattribpointer));
}
void VertexArray::enable() {
	glBindVertexArray(gl_vertex_array_id);
	for (auto& attributepointer : attribute_pointers) {
		glEnableVertexAttribArray(attributepointer.layout);
	}
	glBindVertexArray(0);
}
void VertexArray::clear() {
	if (gl_vertex_array_id != 0) {
		glDeleteVertexArrays(1, &gl_vertex_array_id);
		gl_vertex_array_id = 0;
	}
	attribute_pointers.clear();
}
void VertexArray::disable() {
	glBindVertexArray(gl_vertex_array_id);
	for (auto& attributepointer : attribute_pointers) {
		glDisableVertexAttribArray(attributepointer.layout);
	}
	glBindVertexArray(0);
}
u32 VertexArray::getGlVertexArrayId() const {
	return gl_vertex_array_id;
}