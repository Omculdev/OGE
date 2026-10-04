#include "Rendering/VideoMemory/VertexBufferOrchestrator.hpp"
VertexBufferOrchestrator::VertexBufferOrchestrator(VertexBufferOrchestrator&& other)  noexcept :
	statical_vertex_buffer(std::move(other.statical_vertex_buffer)),
	dynamical_vertex_buffer(std::move(other.dynamical_vertex_buffer)),
	statical_buffer_defragmentation_threshold_bytes(other.statical_buffer_defragmentation_threshold_bytes),
	dynamical_buffer_defragmentation_threshold_bytes(other.dynamical_buffer_defragmentation_threshold_bytes)
{}
VertexBufferOrchestrator& VertexBufferOrchestrator::operator=(VertexBufferOrchestrator&& other) noexcept {
	if (this == &other) return *this;
	statical_vertex_buffer = std::move(other.statical_vertex_buffer);
	dynamical_vertex_buffer = std::move(other.dynamical_vertex_buffer);
	statical_buffer_defragmentation_threshold_bytes = other.statical_buffer_defragmentation_threshold_bytes;
	dynamical_buffer_defragmentation_threshold_bytes = other.dynamical_buffer_defragmentation_threshold_bytes;
	return *this;
}
void VertexBufferOrchestrator::init_members() {
	// change all values later
	statical_vertex_buffer.init(1024 * 1024);
	dynamical_vertex_buffer.init(1024 * 1024);
	statical_buffer_defragmentation_threshold_bytes = 800 * 1024;
	dynamical_buffer_defragmentation_threshold_bytes = 800 * 1024;
}
void VertexBufferOrchestrator::init(u32 staticalbufferusage, u32 dynamicalbufferusage) {
	init_members();
	statical_vertex_buffer.allocateGpuMemory(GL_ARRAY_BUFFER, staticalbufferusage);
	dynamical_vertex_buffer.allocateGpuMemory(GL_ARRAY_BUFFER, dynamicalbufferusage);
}
void VertexBufferOrchestrator::defragment_buffer_and_send_to_gpu(VertexBuffer& buffer, usize defragmentationthreshold) {
	if (buffer.getUsedBufferSize() >= defragmentationthreshold && buffer.needsDefragmentation()) {
		buffer.defragmentBuffer();
		buffer.sendEverythingToGpu(GL_ARRAY_BUFFER);
	}
}
void VertexBufferOrchestrator::updateBuffers() {
	defragment_buffer_and_send_to_gpu(statical_vertex_buffer, statical_buffer_defragmentation_threshold_bytes);
	defragment_buffer_and_send_to_gpu(dynamical_vertex_buffer, dynamical_buffer_defragmentation_threshold_bytes);
}