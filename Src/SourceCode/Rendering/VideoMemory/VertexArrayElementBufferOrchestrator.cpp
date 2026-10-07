#include "Rendering/VideoMemory/VertexArrayElementBufferOrchestrator.hpp"
void VertexArrayElementBufferOrchestrator::init_members(u32 initialelementbufferusage) {
	VertexArrayElementBufferData newvertexarrayelementbufferdata = {};
	newvertexarrayelementbufferdata.vertex_array.init();
	glBindVertexArray(newvertexarrayelementbufferdata.vertex_array.getGlVertexArrayId());
	newvertexarrayelementbufferdata.element_buffer.init(1024 * 1024); // change value later
	newvertexarrayelementbufferdata.element_buffer.allocateGpuMemory(GL_ELEMENT_ARRAY_BUFFER, initialelementbufferusage);
	glBindVertexArray(0);
	newvertexarrayelementbufferdata.defragmentation_threshold = 800 * 1024; // change value later
	newvertexarrayelementbufferdata.enabled = true;
	data.push_back(std::move(newvertexarrayelementbufferdata));
}
void VertexArrayElementBufferOrchestrator::init(u32 initialelementbufferusage) {
	init_members(initialelementbufferusage);
}
VertexArrayElementBufferOrchestrator::VertexArrayElementBufferOrchestrator(VertexArrayElementBufferOrchestrator&& other) noexcept : 
	data(std::move(other.data)),
	free_indices(std::move(other.free_indices))
{}
VertexArrayElementBufferOrchestrator& VertexArrayElementBufferOrchestrator::operator=(VertexArrayElementBufferOrchestrator&& other) noexcept {
	if (this == &other) return *this;
	data = std::move(other.data);
	free_indices = std::move(other.free_indices);
	return *this;
}
[[nodiscard]] VertexArrayElementBufferHandle VertexArrayElementBufferOrchestrator::addVertexArrayElementBuffer(
	usize elementbuffersize,
	usize elementbufferdefragmentationsize,
	u32 elementbufferusage,
	boolean vertexarrayenabled,
	const std::vector<AttributePointer>& attributepointers
) {
	VertexArrayElementBufferData newvertexarrayelementbufferdata = {};
	VertexArrayElementBufferHandle newvertexarrayelementbufferhandle;
	newvertexarrayelementbufferdata.vertex_array.init();
	glBindVertexArray(newvertexarrayelementbufferdata.vertex_array.getGlVertexArrayId());
	newvertexarrayelementbufferdata.element_buffer.init(elementbuffersize);
	newvertexarrayelementbufferdata.element_buffer.allocateGpuMemory(GL_ELEMENT_ARRAY_BUFFER, elementbufferusage);
	for (auto& attributepointer : attributepointers) {
		newvertexarrayelementbufferdata.vertex_array.addAttributePointer(attributepointer);
	}
	if (vertexarrayenabled) newvertexarrayelementbufferdata.vertex_array.enable();
	else newvertexarrayelementbufferdata.vertex_array.disable();
	glBindVertexArray(0);
	if (free_indices.empty()) {
		newvertexarrayelementbufferhandle.setId(data.size()); // implicitly last index + 1
		data.push_back(std::move(newvertexarrayelementbufferdata));
	}
	else {
		u32 freeindex = free_indices.back();
		free_indices.pop_back();
		data[freeindex] = std::move(newvertexarrayelementbufferdata);
		newvertexarrayelementbufferhandle.setId(freeindex);
	}
	return newvertexarrayelementbufferhandle;
}
void VertexArrayElementBufferOrchestrator::deleteVertexArrayElementBuffer(VertexArrayElementBufferHandle& vertexarrayelementbufferhandle) {
	if (vertexarrayelementbufferhandle.getIdValue() == 0) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::deleteVertexArrayElementBuffer: attempting to delete initial vertex array");
		return;
	}
	auto& vertexarrayelementbufferdata = data[vertexarrayelementbufferhandle.getIdValue()];
	vertexarrayelementbufferdata.defragmentation_threshold = 0;
	vertexarrayelementbufferdata.element_buffer.clear();
	vertexarrayelementbufferdata.vertex_array.clear();
	vertexarrayelementbufferdata.enabled = false;
	free_indices.push_back(vertexarrayelementbufferhandle.getIdValue());
	vertexarrayelementbufferhandle.invalidate();
}
void VertexArrayElementBufferOrchestrator::update() {
	for (auto& node : data) {
		if (!node.enabled) {
			continue;
		}
		if (node.element_buffer.getUsedBufferSize() >= node.defragmentation_threshold && node.element_buffer.needsDefragmentation()) {
			node.element_buffer.defragmentBuffer();
			glBindVertexArray(node.vertex_array.getGlVertexArrayId());
			node.element_buffer.sendEverythingToGpu(GL_ELEMENT_ARRAY_BUFFER);
			glBindVertexArray(0);
		}
	}
}
void VertexArrayElementBufferOrchestrator::enableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle) {
	if (!vertexarrayelementbufferhandle.isValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::enableVertexArray: attempted to data via an invalid handle");
		return;
	}
	if (data[vertexarrayelementbufferhandle.getIdValue()].enabled) {
		return;
	}
	data[vertexarrayelementbufferhandle.getIdValue()].enabled = true;
	data[vertexarrayelementbufferhandle.getIdValue()].vertex_array.enable();
}
void VertexArrayElementBufferOrchestrator::disableVertexArray(const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle) {
	if (!vertexarrayelementbufferhandle.isValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::disableVertexArray: attempted to data via an invalid handle");
		return;
	}
	if (!data[vertexarrayelementbufferhandle.getIdValue()].enabled) {
		return;
	}
	data[vertexarrayelementbufferhandle.getIdValue()].enabled = false;
	data[vertexarrayelementbufferhandle.getIdValue()].vertex_array.disable();
}
void VertexArrayElementBufferOrchestrator::addAttributePointer(
	const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle, 
	const AttributePointer& attributepointer
) {
	if (!vertexarrayelementbufferhandle.isValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::enableVertexArray: attempted to data via an invalid handle");
		return;
	}
	data[vertexarrayelementbufferhandle.getIdValue()].vertex_array.addAttributePointer(attributepointer);
}
void VertexArrayElementBufferOrchestrator::deleteAttributePointer(
	const VertexArrayElementBufferHandle& vertexarrayelementbufferhandle, )
[[nodiscard]] VertexArrayElementBufferHandle VertexArrayElementBufferOrchestrator::getInitialHandle() const {
	VertexArrayElementBufferHandle initialvertexarrayelementbufferhandle;
	initialvertexarrayelementbufferhandle.setId(0);
	return initialvertexarrayelementbufferhandle;
}