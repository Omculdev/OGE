#pragma once
#include "Utils/Rendering/VideoMemory/VertexArrayElementBufferHandle.hpp"
#include "Utils/Rendering/VideoMemory/VertexBufferHandle.hpp"
struct ResourceHandle {
	VertexBufferHandle vertex_buffer_handle = {};
	VertexArrayElementBufferHandle vertex_array_element_buffer_handle = {};
};
