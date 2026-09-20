#pragma once
#pragma once
#include "Calculations/General/Types.hpp"
#include "Rendering/VideoMemory/VertexBuffer.hpp"
#include "Rendering/VideoMemory/ElementBuffer.hpp"
class VertexArray {
private:
	u32 gl_vertex_array_id = {};
	struct AttributePointer {
		u32 layout = {};
		u32 type = {};
		usize size = {};
		usize stride = {};
		usize shift = {};
		boolean normalized = {};
	};
	std::vector<AttributePointer> attribute_pointers = {};
	void gen_array();
	void enable_all_attribute_pointers();
public:
	VertexArray() = default;
	void init();
	~VertexArray();
	VertexArray(const VertexArray& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;
	void addAttributePointer(u32 layout, usize size, u32 type, boolean normalized, usize stride, usize shift);
	void create(const VertexBuffer& vertexbuffer, const ElementBuffer& elementbuffer, u32 datausage);
	u32 getGlVertexArrayId() const;
};