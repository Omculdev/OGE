#pragma once
#include "Rendering/VideoMemory/VertexArrayElementBufferOrchestrator.hpp"
#include "Rendering/VideoMemory/VertexBufferOrchestrator.hpp"
#include "Utils/Rendering/VideoMemory/ResourceHandle.hpp"
class ResourceManager {
private:
	VertexArrayElementBufferOrchestrator vertex_array_element_buffer_orchestrator = {};
	VertexBufferOrchestrator vertex_buffer_orchestrator = {};
public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator=(const ResourceManager& other) = delete;
	ResourceManager(ResourceManager&& other) noexcept;
	ResourceManager& operator=(ResourceManager&& other) noexcept;
	template <typename VertexType>
	[[nodiscard]] std::optional<VertexBufferHandle> saveVertexDataAndSendToGpu(
		const std::vector<VertexType> vertices,
		const VertexBufferType vertexbuffertype = VertexBufferType::dynamical,
		boolean active = true
	) {
		auto newvertexbufferhandle = vertex_buffer_orchestrator.saveVertexDataAndSendToGpu<VertexType>(vertices, vertexbuffertype, active);
		if (!newvertexbufferhandle.hasValue()) {
			Logger::getInstance().logWarning("DrawHandler::saveDataAndSendToGpu: invalid vertex buffer handle");
			return std::nullopt;
		}
		return newvertexbufferhandle;
	}
	template <typename ElementType>
	[[nodiscard]] std::optional<ElementBufferHandle> saveElementDataAndSendToGpu(
		const std::vector<ElementType>& elements,
		boolean active = true
	) {
		auto newelementbufferhandle = vertex_array_element_buffer_orchestrator. 
	}
	void addAttributePointer(const AttributePointer& attributepointer);
	template <typename VertexType, typename ElementType>
	[[nodiscard]] ResourceHandle saveDataAndSendToGpu(
		const std::vector<VertexType> vertices,
		const std::vector<ElementType> elements,
	) {
		ResourceHandle newresourcehandle;
		newresourcehandlevertex_array_element_buffer_handle = vertexarrayelementbufferorchestrator.saveElementDataAndSendToGpu(vertexarrayelementbufferorchestrator.getInitialHandle(), elements);
		auto vertexbufferhandle = vertexbufferorchestrator.saveVertexDataAndSendToGpu(vertices, vertexbuffertype);
		if (!vertexbufferhandle.hasValue()) {
			Logger::getInstance().logWarning("DrawHandler::saveDataAndSendToGpu: invalid vertex buffer handle");
			return false;
		}
		newresourcehandle.vertex_buffer_handle = *vertexbufferhandle;
	}
};