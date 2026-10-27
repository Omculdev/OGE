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
void VertexBufferOrchestrator::init_members(
	usize staticalbuffersizebytes,
	usize dynamicalbuffersizebytes, 
	usize staticalbufferdefragmentationthresholdbytes,
	usize dynamicalbufferdefragmentationthresholdbytes
) {
	// change all values later
	statical_vertex_buffer.init(staticalbuffersizebytes);
	dynamical_vertex_buffer.init(dynamicalbuffersizebytes);
	statical_buffer_defragmentation_threshold_bytes = staticalbufferdefragmentationthresholdbytes;
	dynamical_buffer_defragmentation_threshold_bytes = dynamicalbufferdefragmentationthresholdbytes;
}
void VertexBufferOrchestrator::init(
	usize staticalbuffersizebytes,
	usize dynamicalbuffersizebytes,
	usize staticalbufferdefragmentationthresholdbytes,
	usize dynamicalbufferdefragmentationthresholdbytes,
	u32 staticalbufferusage, 
	u32 dynamicalbufferusage
) {
	init_members(
		staticalbuffersizebytes,
		dynamicalbuffersizebytes,
		staticalbufferdefragmentationthresholdbytes,
		dynamicalbufferdefragmentationthresholdbytes
	);
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
void VertexBufferOrchestrator::deleteData(VertexBufferHandle& vertexbufferhandle, const VertexBufferType& vertexbuffertype) {
	switch (vertexbuffertype) {
	case VertexBufferType::none:
	case VertexBufferType::amount:
		Logger::getInstance().logWarning("VertexBufferOrchestrator::deleteData: invalid vertex buffer type");
		return;
	case VertexBufferType::statical:
		statical_vertex_buffer.deleteData(vertexbufferhandle);
		return;
	case VertexBufferType::dynamical:
		dynamical_vertex_buffer.deleteData(vertexbufferhandle);
		return;
	}
}
[[nodiscard]] std::optional<usize> VertexBufferOrchestrator::getVertexBufferOffset(const VertexBufferHandle& vertexbufferhandle, const VertexBufferType& vertexbuffertype) const {
	switch (vertexbuffertype) {
	case VertexBufferType::none:
	case VertexBufferType::amount:
		Logger::getInstance().logWarning("VertexBufferOrchestrator::getVertexBufferOffset: invalid vertex buffer type");
		return std::nullopt;
	case VertexBufferType::statical:
		return statical_vertex_buffer.getOffset(vertexbufferhandle);
	case VertexBufferType::dynamical:
		return dynamical_vertex_buffer.getOffset(vertexbufferhandle);
	}
}
[[nodiscard]] std::optional<u32> VertexBufferOrchestrator::getGlVertexBufferId(const VertexBufferType& vertexbuffertype) const {
	switch (vertexbuffertype) {
	case VertexBufferType::none:
	case VertexBufferType::amount:
		Logger::getInstance().logWarning("VertexBufferOrchestrator::getGlVertexBufferId: invalid vertex buffer type");
		return std::nullopt;
	case VertexBufferType::statical:
		return statical_vertex_buffer.getGlBufferId();
	case VertexBufferType::dynamical:
		return dynamical_vertex_buffer.getGlBufferId();
	}
}