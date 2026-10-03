#pragma once
#include "Utils/Rendering/VideoMemory/VertexBufferHandle.hpp"
#include "Utils/Rendering/VideoMemory/ElementBufferHandle.hpp"
class Mesh {
public:
	ElementBufferHandle element_buffer_handle = {};
	VertexBufferHandle vertex_buffer_handle = {};	
};