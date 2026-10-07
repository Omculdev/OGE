#include "Rendering/DrawHandler.hpp"
DrawHandler::DrawHandler(DrawHandler&& other) noexcept :
	drawable_items(std::move(other.drawable_items)),
	free_indices(std::move(other.free_indices))
{}
DrawHandler& DrawHandler::operator=(DrawHandler&& other) noexcept {
	if (&other == this) return *this;
	drawable_items = std::move(other.drawable_items);
	free_indices = std::move(other.free_indices);
	return *this;
}

