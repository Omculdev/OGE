#include "Rendering/VideoMemory/VertexArrayElementBufferOrchestrator.hpp"
#include "Utils/Calculations/VertexArrayElementBufferIdGenerator.hpp"
void VertexArrayElementBufferOrchestrator::init_initial_vertex_array() {
	VertexArray initialvertexarray;
	initialvertexarray.init();
	vertex_arrays.push_back(std::move(initialvertexarray));
}
void VertexArrayElementBufferOrchestrator::init_initial_element_buffer(u32 initialelementbufferusage) {
	ElementBuffer initialelementbuffer;
	usize initialelementbufferdefragmentationsize = 800 * 1024; // change value later
	element_buffer_defragmentation_sizes.push_back(initialelementbufferdefragmentationsize);
	glBindVertexArray(vertex_arrays[0].getGlVertexArrayId());
	initialelementbuffer.init(1024*1024); // change value later
	initialelementbuffer.allocateGpuMemory(GL_ELEMENT_ARRAY_BUFFER, initialelementbufferusage);
	glBindVertexArray(0);
	element_buffers.push_back(std::move(initialelementbuffer));
}
void VertexArrayElementBufferOrchestrator::init_members(u32 initialelementbufferusage) {
	init_initial_vertex_array();
	init_initial_element_buffer(initialelementbufferusage);
	disabled_ids.push_back(false);
}
void VertexArrayElementBufferOrchestrator::init(u32 initialelementbufferusage) {
	init_members(initialelementbufferusage);
	VertexArrayElementBufferIdGenerator::increment(); // because added initial
}
VertexArrayElementBufferOrchestrator::VertexArrayElementBufferOrchestrator(VertexArrayElementBufferOrchestrator&& other) noexcept : 
	disabled_ids(std::move(other.disabled_ids)),
	element_buffer_defragmentation_sizes(std::move(other.element_buffer_defragmentation_sizes)),
	vertex_arrays(std::move(other.vertex_arrays)),
	element_buffers(std::move(other.element_buffers))
{}
VertexArrayElementBufferOrchestrator& VertexArrayElementBufferOrchestrator::operator=(VertexArrayElementBufferOrchestrator&& other) noexcept {
	if (this == &other) return *this;
	disabled_ids = std::move(other.disabled_ids);
	element_buffer_defragmentation_sizes= std::move(other.element_buffer_defragmentation_sizes);
	vertex_arrays = std::move(other.vertex_arrays);
	element_buffers = std::move(other.element_buffers);
	return *this;
}
[[nodiscard]] VertexArrayElementBufferHandle VertexArrayElementBufferOrchestrator::addVertexArrayElementBuffer(
	usize elementbuffersize,
	usize elementbufferdefragmentationsize,
	u32 elementbufferusage,
	boolean vertexarrayenabled,
	const std::vector<AttributePointer>& attributepointers
) {
	VertexArray newvertexarray;
	ElementBuffer newelementbuffer;
	VertexArrayElementBufferHandle newvertexarrayelementbufferhandle;
	newvertexarray.init();
	glBindVertexArray(newvertexarray.getGlVertexArrayId());
	newelementbuffer.init(elementbuffersize);
	newelementbuffer.allocateGpuMemory(GL_ELEMENT_ARRAY_BUFFER, elementbufferusage);
	for (auto& attributepointer : attributepointers) {
		newvertexarray.addAttributePointer(attributepointer);
	}
	if (vertexarrayenabled) newvertexarray.enable();
	else newvertexarray.disable();
	glBindVertexArray(0);
	newvertexarrayelementbufferhandle.id = VertexArrayElementBufferIdGenerator::assignId();
	disabled_ids.push_back(false);
	element_buffers.push_back(std::move(newelementbuffer));
	vertex_arrays.push_back(std::move(newvertexarray));
	element_buffer_defragmentation_sizes.push_back(elementbufferdefragmentationsize);
	return newvertexarrayelementbufferhandle;
}
void VertexArrayElementBufferOrchestrator::deleteVertexArrayElementBuffer(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle) {
	if (vertexarrayelementbufferhandle.id == 0) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::deleteVertexArrayElementBuffer: attempting to delete initial vertex array");
		return;
	}
	disabled_ids[vertexarrayelementbufferhandle.id] = true;
	element_buffer_defragmentation_sizes[vertexarrayelementbufferhandle.id] = 0;
	vertex_arrays[vertexarrayelementbufferhandle.id].clear();
	element_buffers[vertexarrayelementbufferhandle.id].clear();
}
void VertexArrayElementBufferOrchestrator::update() {
	for (usize elementbufferindex = 0; elementbufferindex < element_buffers.size(); elementbufferindex++) {
		if (disabled_ids[elementbufferindex]) {
			continue;
		}
		ElementBuffer& elementbuffer = element_buffers[elementbufferindex];
		if (elementbuffer.getUsedBufferSize() >= element_buffer_defragmentation_sizes[elementbufferindex] && elementbuffer.needsDefragmentation()) {
			elementbuffer.defragmentBuffer();
			glBindVertexArray(vertex_arrays[elementbufferindex].getGlVertexArrayId());
			elementbuffer.sendEverythingToGpu(GL_ELEMENT_ARRAY_BUFFER);
			glBindVertexArray(0);
		}
	}
}
void VertexArrayElementBufferOrchestrator::enableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle) {
	if (disabled_ids[vertexarrayelementbufferhandle.id]) {
		return;
	}
	vertex_arrays[vertexarrayelementbufferhandle.id].enable();
}
void VertexArrayElementBufferOrchestrator::disableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle) {
	if (disabled_ids[vertexarrayelementbufferhandle.id]) {
		return;
	}
	vertex_arrays[vertexarrayelementbufferhandle.id].disable();
}
[[nodiscard]] VertexArrayElementBufferHandle VertexArrayElementBufferOrchestrator::getInitialHandle() const {
	VertexArrayElementBufferHandle initialvertexarrayelementbufferhandle;
	initialvertexarrayelementbufferhandle.id = 0;
	return initialvertexarrayelementbufferhandle;
}