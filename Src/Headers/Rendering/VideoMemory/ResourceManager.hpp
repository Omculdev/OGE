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
		u32 initialelementbufferusage = GL_DYNAMIC_DRAW,
		const std::vector<AttributePointer>& attributepointers = {}
	);
	template <typename VertexType>
	[[nodiscard]] std::optional<VertexBufferHandle> saveVertexDataAndSendToGpu(
		const std::vector<VertexType>& vertices,
		const VertexBufferType vertexbuffertype = VertexBufferType::dynamical,
		boolean active = true
	) {
		auto newvertexbufferhandle = vertex_buffer_orchestrator.saveVertexDataAndSendToGpu<VertexType>(vertices, vertexbuffertype, active);
		if (!newvertexbufferhandle.hasValue()) {
			Logger::getInstance().logWarning("ResourceManager::saveVertexDataAndSendToGpu: failed to save vertex bufferdata");
			return std::nullopt;
		}
		return newvertexbufferhandle;
	}
	template <typename ElementType>
	[[nodiscard]] std::optional<ElementBufferHandle> saveElementDataAndSendToGpu(
		const VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		const std::vector<ElementType>& elements,
		boolean active = true
	) {
		std::optional<ElementBufferHandle> newelementbufferhandle = vertex_array_element_buffer_orchestrator.saveElementDataAndSendToGpu<u32>(
			vertexarrayelementbufferattributepointerhandle,
			elements,
			active
		);
		if (!newelementbufferhandle.has_value()) {
			Logger::getInstance().logWarning("ResourceManager::saveElementDataAndSendToGpu: failed to save element buffer data");
			return std::nullopt;
		}
		return newelementbufferhandle;
	}
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
	[[nodiscard]] VertexArrayElementBufferAttributePointerHandle& getInitialVertexArrayElementBufferAttributePointerHandle();
};