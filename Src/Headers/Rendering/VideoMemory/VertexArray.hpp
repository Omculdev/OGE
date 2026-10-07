#pragma once
#include "Calculations/General/Types.hpp"
#include "Rendering/VideoMemory/VertexBuffer.hpp"
#include "Rendering/VideoMemory/ElementBuffer.hpp"
#include "Utils/Rendering/VideoMemory/AttributePointer.hpp"
#include "Utils/Rendering/VideoMemory/AttributePointerHandle.hpp"
class VertexArray {
private:
	u32 gl_vertex_array_id = {};
	std::vector<AttributePointer> attribute_pointers = {};
	std::vector<usize> free_indeces = {};
	void gen_array();
public:
	VertexArray() = default;
	VertexArray(const VertexArray& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;
	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;
	void init();
	~VertexArray();
	[[nodiscard]] AttributePointerHandle addAttributePointer(AttributePointer attributepointer); // copy intended
	[[nodiscard]] AttributePointerHandle addAttributePointer(
		u32 layout, 
		usize size, 
		u32 type, 
		boolean normalized, 
		usize stride, 
		usize shift,
		boolean enabled = true
	);
	void enableAttributePointer(const AttributePointerHandle& attributepointerhandle);
	void disableAttributePointer(const AttributePointerHandle& attributepointerhandle);
	void enableAllAttributePointers();
	void disableAllAttributePointers();
	void clear();
	u32 getGlVertexArrayId() const;
};