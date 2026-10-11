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
	u32 initialelementbufferusage,
	const std::vector<AttributePointer>& attributepointers
) {
	vertex_buffer_orchestrator.init(
		staticalvertexbuffersizebytes, dynamicalvertexbuffersizebytes,
		staticalvertexbufferdefragmentationthresholdbytes, dynamicalvertexbufferdefragmentationthresholdbytes,
		staticalvertexbufferusage, dynamicalvertexbufferusage
	);
	initial_vertex_array_element_buffer_attribute_pointer_handle = vertex_array_element_buffer_orchestrator.init(
		initialelementbuffersizebytes,
		initialelementbufferdefragmentationthresholdbytes,
		initialelementbufferusage,
		attributepointers
	);
}
void ResourceManager::update() {
	vertex_buffer_orchestrator.updateBuffers();
	vertex_array_element_buffer_orchestrator.update();
}
[[nodiscard]] VertexArrayElementBufferAttributePointerHandle& ResourceManager::getInitialVertexArrayElementBufferAttributePointerHandle() {
	return initial_vertex_array_element_buffer_attribute_pointer_handle;
}
