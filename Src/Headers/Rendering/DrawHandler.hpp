#pragma once
#include "Graphics/2D/Drawable/Rectangle.hpp"
#include "Rendering/Shaders/ShaderOrchestator.hpp"
#include "Rendering/VideoMemory/ResourceManager.hpp"
#include <Calculations/General/Types.hpp>
#include <GLAD/glad.h>
#include <Utils/Enums/VertexBufferTypes.hpp>
#include <Utils/General/Logger.hpp>
#include <Utils/Rendering/VideoMemory/ResourceHandle.hpp>
#include <Utils/Rendering/VideoMemory/Vertex.hpp>
#include <Utils/Rendering/VideoMemory/VertexArrayElementBufferAttributePointerHandle.hpp>
#include <Utils/Rendering/VideoMemory/VertexBufferHandle.hpp>
#include <algorithm>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>
class DrawHandler {
private:
	struct CommonElementBufferAllocation {
		boolean data_saved = {};
		ElementBufferHandle allocation_handle = {};
	};
	std::vector<ResourceHandle> drawable_item_resource_handles = {};
	std::vector<usize> free_indices = {};
	CommonElementBufferAllocation common_rectangle_element_buffer_allocation = {};
public:
	DrawHandler() = default;
	DrawHandler(const DrawHandler& other) = delete;
	DrawHandler& operator=(const DrawHandler& other) = delete;
	DrawHandler(DrawHandler&& other) noexcept;
	DrawHandler& operator=(DrawHandler&& other) noexcept;
	template <typename RectangleType>
	requires std::is_arithmetic_v<RectangleType>
	void saveRectangleDataAndSendToGpu(
		ResourceManager& resourcemanager,
		VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		Rectangle<RectangleType>& rectangle,
		const VertexBufferType& vertexbuffertype
	) {
		ResourceHandle newresourcehandle = {};
		if (!common_rectangle_element_buffer_allocation.data_saved) {
			std::vector<u32> indices = { 0, 1, 3, 0, 2, 3 };
			std::optional<ElementBufferHandle> newelementbufferhandle = resourcemanager.vertex_array_element_buffer_orchestrator.saveElementDataAndSendToGpu<u32>(
				vertexarrayelementbufferattributepointerhandle,
				indices,
				true
			);
			if (!newelementbufferhandle.has_value()) {
				Logger::getInstance().logWarning("DrawHandler::saveRectangleDataAndSendToGpu: failed to save element buffer data");
				return;
			}
			common_rectangle_element_buffer_allocation.allocation_handle = std::move(*newelementbufferhandle);
			common_rectangle_element_buffer_allocation.data_saved = true;
		}
		std::optional<VertexBufferHandle> newvertexbufferhandle = resourcemanager.vertex_buffer_orchestrator.saveVertexDataAndSendToGpu<Vertex>(
			rectangle.getFullVertexData(),
			vertexbuffertype,
			true
		);
		if (!newvertexbufferhandle.has_value()) {
			Logger::getInstance().logWarning("DrawHandler::saveRectangleDataAndSendToGpu: failed to save vertex buffer data");
			return;
		}
		std::optional<u32> glvertexarrayid = resourcemanager.vertex_array_element_buffer_orchestrator.getGlVertexArrayId(vertexarrayelementbufferattributepointerhandle);
		if (!glvertexarrayid.has_value()) {
			Logger::getInstance().logWarning("DrawHandler::saveRectangleDataAndSendToGpu: failed to acquire a valid gl vertex array id");
			return;
		}
		newresourcehandle.setVertexBufferHandle(std::move(*newvertexbufferhandle));
		newresourcehandle.setVertexBufferType(vertexbuffertype);
		newresourcehandle.setGlVertexArrayId(*glvertexarrayid);
		newresourcehandle.setIndexCount(6); // because 1 rectangle == 2 triangles
		newresourcehandle.setIndexType(GL_UNSIGNED_INT);
		newresourcehandle.setUsesSharedElementBuffer();
		if (free_indices.empty()) {
			rectangle.setDrawId(drawable_item_resource_handles.size()); // implicitly last index +1
			drawable_item_resource_handles.push_back(std::move(newresourcehandle));
		}
		else {
			usize freeindex = free_indices.back();
			free_indices.pop_back();
			rectangle.setDrawId(freeindex);
			drawable_item_resource_handles[freeindex] = std::move(newresourcehandle);
		}
	}
	template <typename RectangleType>
	requires std::is_arithmetic_v<RectangleType>
	void updateRectangleDataAndSendToGpu(
		ResourceManager& resourcemanager,
		VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		Rectangle<RectangleType>& rectangle
	) {
		if (!rectangle.getDrawId().has_value()) {
			Logger::getInstance().logWarning("DrawHandler::updateRectangleDataAndSendToGpu: attempted to update an invalid drawable");
			return;
		}
		ResourceHandle& resourcehandle = drawable_item_resource_handles[rectangle.getDrawIdValue()];
		resourcemanager.vertex_buffer_orchestrator.updateVertexDataAndSendToGpu<Vertex>(
			resourcehandle.getVertexBufferHandle(),
			rectangle.getFullVertexData(),
			resourcehandle.getVertexBufferType(),
			true
		);
	}
	template <typename RectangleType>
	requires std::is_arithmetic_v<RectangleType>
	void deleteDrawable(
		ResourceManager& resourcemanager,
		VertexArrayElementBufferAttributePointerHandle& vertexarrayattributepointerhandle,
		Rectangle<RectangleType>& rectangle
	) {
		std::optional<u32> drawid = rectangle.getDrawId();
		if (!drawid.has_value()) {
			Logger::getInstance().logWarning("DrawHandler::deleteDrawable: attempting to delete an invalid drawable");
			return;
		}
		ResourceHandle& rectangleresourcehandle = drawable_item_resource_handles[*drawid];
		resourcemanager.deleteData(vertexarrayattributepointerhandle, rectangleresourcehandle, true, !rectangleresourcehandle.getUsesSharedElementBuffer());
		free_indices.push_back(*drawid);
		rectangle.resetDrawId();
	}
	template <typename RectangleType>
		requires std::is_arithmetic_v<RectangleType>
	void draw(
		ResourceManager& resourcemanager,
		VertexArrayElementBufferAttributePointerHandle& vertexarrayelementbufferattributepointerhandle,
		Rectangle<RectangleType>& rectangle,
		const VertexBufferType& vertexbuffertype,
		const ShaderOrchestrator& shaderorchestrator
	) {
		if (!rectangle.getDrawId().has_value()) {
			saveRectangleDataAndSendToGpu<RectangleType>(
				resourcemanager,
				vertexarrayelementbufferattributepointerhandle,
				rectangle,
				vertexbuffertype
			);
			rectangle.setClean();
		}
		else if (!rectangle.isClean()) {
			updateRectangleDataAndSendToGpu<RectangleType>(
				resourcemanager,
				vertexarrayelementbufferattributepointerhandle,
				rectangle
			);
		}
		if (!rectangle.getDrawId().has_value()) {
			Logger::getInstance().logWarning("DrawHandler::draw: failed to save rectangle data");
			return;
		}
		const ResourceHandle& resourcehandle = drawable_item_resource_handles[rectangle.getDrawIdValue()];
		shaderorchestrator.useShaderProgram();
		std::optional<usize> vertexoffset = resourcemanager.vertex_buffer_orchestrator.getVertexBufferOffset(
			resourcehandle.getVertexBufferHandle(),
			resourcehandle.getVertexBufferType()
		);
		if (!vertexoffset.has_value()) {
			Logger::getInstance().logWarning("DrawHandler::draw: failed to acquire vertex offset");
			return;
		}
		i32 basevertex = *vertexoffset / sizeof(Vertex);
		glBindVertexArray(resourcehandle.getGlVertexArrayId());
		glDrawElementsBaseVertex(
			GL_TRIANGLES,
			resourcehandle.getIndexCount(),
			resourcehandle.getIndexType(),
			reinterpret_cast<void*>(0),
			basevertex
		);
	}
};