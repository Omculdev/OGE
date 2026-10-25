#include "Rendering/DrawHandler.hpp"
DrawHandler::DrawHandler(DrawHandler&& other) noexcept :
	drawable_item_resource_handles(std::move(other.drawable_item_resource_handles)),
	free_indices(std::move(other.free_indices))
{}
DrawHandler& DrawHandler::operator=(DrawHandler&& other) noexcept {
	if (&other == this) return *this;
	drawable_item_resource_handles = std::move(other.drawable_item_resource_handles);
	free_indices = std::move(other.free_indices);
	return *this;
}
