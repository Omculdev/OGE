#pragma once
#include "Utils/VideoMemory/VertexBufferHandle.hpp"
#include "Utils/VideoMemory/ElementBufferHandle.hpp"
class Mesh {
public:
	ElementBufferHandle element_buffer_handle = {};
	VertexBufferHandle vertex_buffer_handle = {};	
};