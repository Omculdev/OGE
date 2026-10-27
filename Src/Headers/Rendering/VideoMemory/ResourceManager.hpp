#pragma once
#include "Rendering/VideoMemory/VertexArrayElementBufferOrchestrator.hpp"
#include "Rendering/VideoMemory/VertexBufferOrchestrator.hpp"
#include "Utils/Rendering/VideoMemory/ResourceHandle.hpp"
class ResourceManager {
	VertexArrayElementBufferAttributePointerHandle initial_vertex_array_element_buffer_attribute_pointer_handle = {};
public:
	VertexArrayElementBufferOrchestrator vertex_array_element_buffer_orchestrator = {};
	VertexBufferOrchestrator vertex_buffer_orchestrator = {};
	ResourceManager() = default;
	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator=(const ResourceManager& other) = delete;
	ResourceManager(ResourceManager&& other) noexcept;
	ResourceManager& operator=(ResourceManager&& other) noexcept;
	void init(
		usize staticalvertexbuffersizebytes = 1024 * 1024,
		usize dynamicalvertexbuffersizebytes = 1024 * 1024,
		usize staticalvertexbufferdefragmentationthresholdbytes = 800 * 1024,
		usize dynamicalvertexbufferdefragmentationthresholdbytes = 800 * 1024,
		u32 staticalvertexbufferusage = GL_STATIC_DRAW,
		u32 dynamicalvertexbufferusage = GL_DYNAMIC_DRAW,
		usize initialelementbuffersizebytes = 1024 * 1024,
		usize initialelementbufferdefragmentationthresholdbytes = 800 * 1024,
		u32 initialelementbufferusage = GL_DYNAMIC_DRAW
	);
	template <typename VertexType, typename ElementType>
	[[nodiscard]] std::optional<ResourceHandle> saveDataAndSendToGpu(
		const std::vector<VertexType>& vertices,
		const VertexBufferType& vertexbuffertype,
		const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		const std::vector<ElementType>& elements,
		boolean vertexbufferactive = true,
		boolean elementbufferactive = true
	) {
		ResourceHandle newresourcehandle;
		std::optional<VertexBufferHandle> newvertexbufferhandle = {};
		std::optional<ElementBufferHandle> newelementbufferhandle = {};
		newresourcehandle.setVertexBufferType(vertexbuffertype);
		newvertexbufferhandle = saveVertexDataAndSendToGpu<VertexType>(vertices, vertexbuffertype, vertexbufferactive);
		if (!newvertexbufferhandle.has_value()) {
			Logger::getInstance().logWarning("ResourceManager::saveDataAndSendToGpu: failed to save vertex buffer data");
			return std::nullopt;
		}
		newresourcehandle.setVertexBufferHandle(std::move(*newvertexbufferhandle));
		newelementbufferhandle = saveElementDataAndSendToGpu<ElementType>(vertexarrayelementbufferattributepointerhandle, elements, elementbufferactive);
		if (!newelementbufferhandle.has_value()) {
			Logger::getInstance().logWarning("ResourceManager::saveDataAndSendToGpu: failed to save element buffer data");
			return std::nullopt;
		}
		newresourcehandle.setElementBufferHandle(std::move(*newelementbufferhandle));
		return newresourcehandle;
	}
	void update();
	void deleteData(
		const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		ResourceHandle& resourcehandle,
		boolean deletevertexbufferdata = true,
		boolean deleteelementbufferdata = true
	);
	[[nodiscard]] VertexArrayElementBufferAttributePointerHandle& getInitialVertexArrayElementBufferAttributePointerHandle();
};