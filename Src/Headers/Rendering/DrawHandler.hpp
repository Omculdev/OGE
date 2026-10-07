#pragma once
#include <type_traits>
#include "Rendering/VideoMemory/VertexArrayElementBufferOrchestrator.hpp"
#include "Rendering/VideoMemory/VertexBufferOrchestrator.hpp"
#include "Graphics/2D/Drawable/Rectangle.hpp"
class DrawHandler {
private:
	struct DrawableItem {
		VertexArrayElementBufferHandle vertex_array_element_buffer_handle = {};
		VertexBufferHandle vertex_buffer_handle = {};
	};
	std::vector<DrawableItem> drawable_items = {};
	std::vector<usize> free_indices = {};
public:
	DrawHandler() = default;
	DrawHandler(const DrawHandler& other) = delete;
	DrawHandler& operator=(const DrawHandler& other) = delete;
	DrawHandler(DrawHandler&& other) noexcept;
	DrawHandler& operator=(DrawHandler&& other) noexcept;
	template <typename VertexType, typename ElementType>
	[[nodiscard]] boolean saveDrawableItemDataAndSendToGpu(
		VertexArrayElementBufferOrchestrator& vertexarrayelementbufferorchestrator,
		VertexBufferOrchestrator& vertexbufferorchestrator,
		const VertexBufferType& vertexbuffertype,
		const std::vector<VertexType> vertices,
		const std::vector<ElementType> elements,
		usize itemelementbufferoffset,
		usize itemelementbuffersize
	) {
		DrawableItem newdrawableitem;
		newdrawableitem.vertex_array_element_buffer_handle = vertexarrayelementbufferorchestrator.saveElementDataAndSendToGpu(vertexarrayelementbufferorchestrator.getInitialHandle(), elements);
		auto vertexbufferhandle = vertexbufferorchestrator.saveVertexDataAndSendToGpu(vertices, vertexbuffertype);
		if (!vertexbufferhandle.hasValue()) {
			Logger::getInstance().logWarning("DrawHandler::saveDrawableItemDataAndSendToGpu: invalid vertex buffer handle");
			return false;
		}
		newdrawableitem.vertex_buffer_handle = *vertexbufferhandle;


	}
	template <typename RectangleType>
	requires std::is_arithmetic_v<RectangleType>
	void draw(const Rectangle<RectangleType>& rectangle) {

	}
};