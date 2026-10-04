#include "Rendering/VideoMemory/VertexArray.hpp"
#include <Calculations/General/Types.hpp>
#include <GLAD/glad.h>
#include <Rendering/VideoMemory/ElementBuffer.hpp>
#include <Rendering/VideoMemory/VertexBuffer.hpp>
#include <utility>
void VertexArray::gen_array() {
	glGenVertexArrays(1, &gl_vertex_array_id);
}
void VertexArray::init() {
	gen_array();
}
VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &gl_vertex_array_id);
}
void VertexArray::addAttributePointer(u32 layout, usize size, u32 type, boolean normalized, usize stride, usize shift, boolean enabled) {
	AttributePointer newattribpointer;
	newattribpointer.layout = layout;
	newattribpointer.size = size;
	newattribpointer.type = type;
	newattribpointer.normalized = normalized;
	newattribpointer.stride = stride;
	newattribpointer.shift = shift;
	newattribpointer.enabled = enabled;
	attribute_pointers.push_back(std::move(newattribpointer));
}
void VertexArray::enable_all_attribute_pointers() {
	for (auto& attributepointer : attribute_pointers) {
		if (attributepointer.enabled) {
			glVertexAttribPointer(attributepointer.layout, attributepointer.size, attributepointer.type, attributepointer.normalized, attributepointer.stride, reinterpret_cast<void*>(attributepointer.shift));
			glEnableVertexAttribArray(attributepointer.layout);
		}
	}
}
void VertexArray::create(u32 datausage) {
	glBindVertexArray(gl_vertex_array_id);
	enable_all_attribute_pointers();
	glBindVertexArray(0);
}
u32 VertexArray::getGlVertexArrayId() const {
	return gl_vertex_array_id;
}