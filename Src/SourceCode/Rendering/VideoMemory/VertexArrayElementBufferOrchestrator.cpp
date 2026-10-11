#include "Rendering/VideoMemory/VertexArrayElementBufferOrchestrator.hpp"
[[nodiscard]] VertexArrayElementBufferAttributePointerHandle VertexArrayElementBufferOrchestrator::addVertexArrayElementBuffer(
	usize elementbuffersize,
	usize elementbufferdefragmentationsize,
	u32 elementbufferusage,
	const std::vector<AttributePointer>& attributepointers
) {
	VertexArrayElementBufferData newvertexarrayelementbufferdata = {};
	VertexArrayElementBufferAttributePointerHandle newvertexarrayelementbufferattributepointerhandle = {};
	newvertexarrayelementbufferdata.vertex_array.init();
	glBindVertexArray(newvertexarrayelementbufferdata.vertex_array.getGlVertexArrayId());
	newvertexarrayelementbufferdata.element_buffer.init(elementbuffersize);
	newvertexarrayelementbufferdata.element_buffer.allocateGpuMemory(GL_ELEMENT_ARRAY_BUFFER, elementbufferusage);
	for (usize attributepointerindex = 0; attributepointerindex < attributepointers.size(); attributepointerindex++) {
		AttributePointer attributepointer = attributepointers[attributepointerindex];
		AttributePointerHandle attributepointerhandle = newvertexarrayelementbufferdata.vertex_array.addAttributePointer(attributepointer);
		newvertexarrayelementbufferattributepointerhandle.addAttributePointerHandle(std::move(attributepointerhandle));
	}
	glBindVertexArray(0);
	if (free_indices.empty()) {
		newvertexarrayelementbufferattributepointerhandle.setVertexArrayElementBufferHandleId(data.size()); // implicitly last index + 1
		data.push_back(std::move(newvertexarrayelementbufferdata));
	}
	else {
		u32 freeindex = free_indices.back();
		free_indices.pop_back();
		data[freeindex] = std::move(newvertexarrayelementbufferdata);
		newvertexarrayelementbufferattributepointerhandle.setVertexArrayElementBufferHandleId(freeindex);
	}
	return newvertexarrayelementbufferattributepointerhandle;
}
[[nodiscard]] VertexArrayElementBufferAttributePointerHandle VertexArrayElementBufferOrchestrator::init_members(
	u32 initialelementbufferusage,
	usize initialelementbuffersizebytes,
	usize initialelementbufferdefragmentationthresholdbytes,
	const std::vector<AttributePointer>& attributepointers
) {
	return addVertexArrayElementBuffer(
		initialelementbuffersizebytes,
		initialelementbufferdefragmentationthresholdbytes,
		initialelementbufferusage,
		attributepointers
	);
}
[[nodiscard]] VertexArrayElementBufferAttributePointerHandle VertexArrayElementBufferOrchestrator::init(
	usize initialelementbuffersizebytes,
	usize initialelementbufferdefragmentationthresholdbytes,
	u32 initialelementbufferusage,
	const std::vector<AttributePointer>& attributepointers
) {
	return init_members(
		initialelementbufferusage,
		initialelementbuffersizebytes,
		initialelementbufferdefragmentationthresholdbytes,
		attributepointers
	);
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
void VertexArrayElementBufferOrchestrator::deleteVertexArrayElementBuffer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle) {
	if (vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue() == 0) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::deleteVertexArrayElementBuffer: attempting to delete initial vertex array");
		return;
	}
	u32 id = vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue();
	auto& vertexarrayelementbufferdata = data[id];
	for (auto& attributepointerhandle : vertexarrayelementbufferattributepointerhandle.getAllAttributePointerHandles()) {
		vertexarrayelementbufferdata.vertex_array.deleteAttributePointer(attributepointerhandle);
	}
	vertexarrayelementbufferdata.defragmentation_threshold = 0;
	vertexarrayelementbufferdata.element_buffer.clear();
	vertexarrayelementbufferdata.vertex_array.clear();
	free_indices.push_back(id);
	vertexarrayelementbufferattributepointerhandle.invalidateVertexArrayElementBufferHandle();
}
void VertexArrayElementBufferOrchestrator::update() {
	for (auto& node : data) {
		if (node.element_buffer.needsDefragmentation()) { // always false for a deleted buffer
			if (node.element_buffer.getUsedBufferSize() >= node.defragmentation_threshold) {
				node.element_buffer.defragmentBuffer();
				glBindVertexArray(node.vertex_array.getGlVertexArrayId());
				node.element_buffer.sendEverythingToGpu(GL_ELEMENT_ARRAY_BUFFER);
				glBindVertexArray(0);
			}
		}
	}
}
void VertexArrayElementBufferOrchestrator::enableAllAttributePointers(const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle) {
	if (!vertexarrayelementbufferattributepointerhandle.isVertexArrayElementBufferHandleValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::enableAllAttributePointers: attempted to access data via an invalid handle");
		return;
	}
	u32 id = vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue();
	data[id].vertex_array.enableAllAttributePointers();
}
void VertexArrayElementBufferOrchestrator::disableAllAttributePointers(const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle) {
	if (!vertexarrayelementbufferattributepointerhandle.isVertexArrayElementBufferHandleValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::disableAllAttributePointers: attempted to access data via an invalid handle");
		return;
	}
	u32 id = vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue();
	data[id].vertex_array.disableAllAttributePointers();
}
void VertexArrayElementBufferOrchestrator::addAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, const AttributePointer& attributepointer) {
	if (!vertexarrayelementbufferattributepointerhandle.isVertexArrayElementBufferHandleValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::addAttributePointer: attempted to access data via an invalid handle");
		return;
	}
	u32 id = vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue();
	AttributePointerHandle newattributepointerhandle = data[id].vertex_array.addAttributePointer(attributepointer);
	vertexarrayelementbufferattributepointerhandle.addAttributePointerHandle(std::move(newattributepointerhandle));
}
void VertexArrayElementBufferOrchestrator::addAttributePointer(
	VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
	u32 layout,
	usize size,
	u32 type,
	boolean normalized,
	usize stride,
	usize shift,
	boolean enabled
) {
	AttributePointer newattributepointer = {};
	newattributepointer.layout = layout;
	newattributepointer.size = size;
	newattributepointer.type = type;
	newattributepointer.normalized = normalized;
	newattributepointer.stride = stride;
	newattributepointer.shift = shift;
	newattributepointer.enabled = enabled;
	newattributepointer.active = true;
	addAttributePointer(vertexarrayelementbufferattributepointerhandle, newattributepointer);
}
void VertexArrayElementBufferOrchestrator::deleteAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, usize handleindex) {
	if (!vertexarrayelementbufferattributepointerhandle.isVertexArrayElementBufferHandleValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::deleteAttributePointer: attempted to access data via an invalid handle");
		return;
	}
	u32 id = vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue();
	AttributePointerHandle& attributepointerhandle = vertexarrayelementbufferattributepointerhandle.getAttributePointerHandle(handleindex);
	data[id].vertex_array.deleteAttributePointer(attributepointerhandle);	
	vertexarrayelementbufferattributepointerhandle.deleteAttributePointerHandle(handleindex);
}
void VertexArrayElementBufferOrchestrator::enableAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, usize handleindex) {
	if (!vertexarrayelementbufferattributepointerhandle.isVertexArrayElementBufferHandleValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::enableAttributePointer: attempted to access data via an invalid handle");
		return;
	}
	u32 id = vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue();
	AttributePointerHandle& attributepointerhandle = vertexarrayelementbufferattributepointerhandle.getAttributePointerHandle(handleindex);
	data[id].vertex_array.enableAttributePointer(attributepointerhandle);
}
void VertexArrayElementBufferOrchestrator::disableAttributePointer(VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle, usize handleindex) {
	if (!vertexarrayelementbufferattributepointerhandle.isVertexArrayElementBufferHandleValid()) {
		Logger::getInstance().logWarning("VertexArrayElementBufferOrchestrator::disbleAttributePointer: attempted to access data via an invalid handle");
		return;
	}
	u32 id = vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleIdValue();
	AttributePointerHandle& attributepointerhandle = vertexarrayelementbufferattributepointerhandle.getAttributePointerHandle(handleindex);
	data[id].vertex_array.disableAttributePointer(attributepointerhandle);
}
