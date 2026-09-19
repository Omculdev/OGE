#pragma once
#include "Calculations/General/Types.hpp"
#include "Utils/Enums/Axes.hpp"
class MathUtils {
public:
	static f32 normalize_color(u8 color);
	static f32 normalize_position_2d(f64 position, Axis axis);
};