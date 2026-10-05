#pragma once
#pragma once
#include "Calculations/General/Types.hpp"
#include "Rendering/VideoMemory/VertexBuffer.hpp"
#include "Rendering/VideoMemory/ElementBuffer.hpp"
#include "Utils/Rendering/VideoMemory/AttributePointer.hpp"
class VertexArray {
private:
	u32 gl_vertex_array_id = {};
	std::vector<AttributePointer> attribute_pointers = {};
	void gen_array();
public:
	VertexArray() = default;
	VertexArray(const VertexArray& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;
	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;
	void init();
	~VertexArray();
	VertexArray(const VertexArray& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;
	void addAttributePointer(const AttributePointer& attributepointer);
	void addAttributePointer(u32 layout, usize size, u32 type, boolean normalized, usize stride, usize shift);
	void clear();
	void enable();
	void disable();
	u32 getGlVertexArrayId() const;
};