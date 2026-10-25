#include "Rendering/VideoMemory/ResourceManager.hpp"
ResourceManager::ResourceManager(ResourceManager&& other) noexcept :
	vertex_buffer_orchestrator(std::move(other.vertex_buffer_orchestrator)),
	vertex_array_element_buffer_orchestrator(std::move(other.vertex_array_element_buffer_orchestrator)),
	initial_vertex_array_element_buffer_attribute_pointer_handle(std::move(other.initial_vertex_array_element_buffer_attribute_pointer_handle))
{}
ResourceManager& ResourceManager::operator=(ResourceManager&& other) noexcept {
	if (&other == this) return *this;
	vertex_buffer_orchestrator = std::move(other.vertex_buffer_orchestrator);
	vertex_array_element_buffer_orchestrator = std::move(other.vertex_array_element_buffer_orchestrator);
	initial_vertex_array_element_buffer_attribute_pointer_handle = std::move(other.initial_vertex_array_element_buffer_attribute_pointer_handle);
	return *this;
}
void ResourceManager::init(
	usize staticalvertexbuffersizebytes,
	usize dynamicalvertexbuffersizebytes,
	usize staticalvertexbufferdefragmentationthresholdbytes,
	usize dynamicalvertexbufferdefragmentationthresholdbytes,
	u32 staticalvertexbufferusage,
	u32 dynamicalvertexbufferusage,
	usize initialelementbuffersizebytes,
	usize initialelementbufferdefragmentationthresholdbytes,
	u32 initialelementbufferusage
) {
	vertex_buffer_orchestrator.init(
		staticalvertexbuffersizebytes, dynamicalvertexbuffersizebytes,
		staticalvertexbufferdefragmentationthresholdbytes, dynamicalvertexbufferdefragmentationthresholdbytes,
		staticalvertexbufferusage, dynamicalvertexbufferusage
	);
	initial_vertex_array_element_buffer_attribute_pointer_handle = vertex_array_element_buffer_orchestrator.init(
		initialelementbuffersizebytes,
		initialelementbufferdefragmentationthresholdbytes,
		initialelementbufferusage
	);
}
void ResourceManager::update() {
	vertex_buffer_orchestrator.updateBuffers();
	vertex_array_element_buffer_orchestrator.update();
}
void ResourceManager::deleteData(
	const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
	ResourceHandle& resourcehandle,
	boolean deletevertexbufferdata,
	boolean deleteelementbufferdata
) {
	if (deletevertexbufferdata) {
		if (!resourcehandle.getVertexBufferHandle().isValid()) {
			Logger::getInstance().logWarning("ResourceManager::getData: attempted to access vertex buffer data via an invalid handle");
		}
		else {
			vertex_buffer_orchestrator.deleteData(resourcehandle.getVertexBufferHandle(), resourcehandle.getVertexBufferType());
		}
	}
	if (deleteelementbufferdata) {
		if (!vertexarrayelementbufferattributepointerhandle.getVertexArrayElementBufferHandleId().has_value()) {
			Logger::getInstance().logWarning("ResourceManager::getData: attempted to access vertex array element buffer data via an invalid handle");
		}
		else if (!resourcehandle.getElementBufferHandle().isValid()) {
			Logger::getInstance().logWarning("ResourceManager::getData: attempted to access element buffer data via an invalid handle");
		}
		else {
			vertex_array_element_buffer_orchestrator.deleteElementBufferData(vertexarrayelementbufferattributepointerhandle, resourcehandle.getElementBufferHandle());
		}
	}
	resourcehandle.invalidate();
}
[[nodiscard]] VertexArrayElementBufferAttributePointerHandle& ResourceManager::getInitialVertexArrayElementBufferAttributePointerHandle() {
	return initial_vertex_array_element_buffer_attribute_pointer_handle;
}
