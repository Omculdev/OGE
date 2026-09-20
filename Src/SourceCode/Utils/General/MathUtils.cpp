	#include "Utils/General/MathUtils.hpp"
#include <GLAD/glad.h>
#include <algorithm>
#include <cassert>
f32 MathUtils::normalize_color(u8 color) {
	return static_cast<f32>(color) / static_cast<f32>(255);
}
f32 MathUtils::normalize_position_2d(f64 position, Axis axis) {
	assert(axis != Axis::z, "Renderer::normalize_position_2d: cannot normalize a 2D position for Z axis");
	i32 viewport[4] = {};
	glGetIntegerv(GL_VIEWPORT, viewport);
	i32 width = viewport[2];
	i32 height = viewport[3];
	switch (axis) {
	case Axis::x:
		return static_cast<f32>((position / width) * 2.0 - 1.0);
	case Axis::y:
		return static_cast<f32>(((position / height) * 2.0 - 1.0));
	default:
		return NAN;
	}
}