#include "Rendering/VideoMemory/BufferOrchestrator.hpp"
// depricated
void BufferOrchestrator::create_initial_element_buffer() {
	ElementBuffer initialbuffer;
	initialbuffer.init(1024 * 1024); // change value later
	element_buffers.push_back(std::move(initialbuffer));
}
void BufferOrchestrator::create_vertex_buffer() {
	vertex_buffer.init(1024 * 1024); // change value later
}
void BufferOrchestrator::init_initial_element_buffer(const VertexArray& vertexarray, u32 elementbufferusage) {
	glBindVertexArray(vertexarray.getGlVertexArrayId()); // EBO is bound to a VAO
	element_buffers[0].allocateGpuMemory(GL_ELEMENT_ARRAY_BUFFER, elementbufferusage); // 0 is initial
	glBindVertexArray(0);
	element_buffer_defragmentation_threshold_bytes = 1024; //change value later
}
void BufferOrchestrator::init_vertex_buffer(u32 vertexbufferusage) {
	vertex_buffer.allocateGpuMemory(GL_ARRAY_BUFFER, vertexbufferusage);
	vertex_buffer_defragmentation_threshold_bytes = 1024; // change value later
}
void BufferOrchestrator::init_members(const VertexArray& vertexarray, u32 vertexbufferusage, u32 elementbufferusage) {
	create_initial_element_buffer();
	create_vertex_buffer();
	init_initial_element_buffer(vertexarray, elementbufferusage);
	init_vertex_buffer(vertexbufferusage);
}
void BufferOrchestrator::init(const VertexArray& vertexarray, u32 vertexbufferusage, u32 elementbufferusage) {
	init_members(vertexarray, vertexbufferusage, elementbufferusage);
}
void BufferOrchestrator::send_latest_data_to_gpu_and_save_to_vertex_array(
	const VertexArray& vertexarray,
	u32 vertexbufferusage,
	u32 elementbufferusage,
	usize elementbufferindex
) {
	glBindVertexArray(vertexarray.getGlVertexArrayId());
	vertex_buffer.sendDataToGpu(GL_ARRAY_BUFFER, vertexbufferusage);
	element_buffers[elementbufferindex].sendDataToGpu(GL_ELEMENT_ARRAY_BUFFER, elementbufferusage);
	glBindVertexArray(0);
}
void BufferOrchestrator::updateBuffers(std::vector<usize> elementbufferindecestoclear) {
	for (auto& index : elementbufferindecestoclear) {
		if (element_buffers[index].getUsedBufferSize() >= element_buffer_defragmentation_threshold_bytes) {
			element_buffers[index].defragmentBuffer();
		}
	}
	if (vertex_buffer.getUsedBufferSize() >= vertex_buffer_defragmentation_threshold_bytes) {
		vertex_buffer.defragmentBuffer();
	}
}