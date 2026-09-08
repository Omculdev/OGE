#pragma once
#include "Calculations/General/Types.hpp"
#include "Calculations/2D/Vec2.hpp"
#include <GLAD/glad.h>
#include <concepts>
#include <type_traits>
#include <cmath>
#include <optional>
template <typename Type>
requires std::is_arithmetic_v<Type>
class Point2 {
public:
	Type x = {};
	Type y = {};
	Point2() = default;
	Point2(const Point2& other) = default;
	Point2(Point2&& other) noexcept = default;
	Point2& operator=(const Point2& other) = default;
	Point2& operator=(Point2&& other) noexcept = default;
	~Point2() = default;
	Point2(Type x, Type y) : x(x), y(y) {}
	explicit Point2(Type value) : x(value), y(value) {}
	Point2 operator+(const Vec2& vec2) const {
		return Point2(x + vec2.x, y + vec2.y);
	}
	Point2 operator-(const Vec2& vec2) const {
		return Point2(x - vec2.x, y - vec2.y);
	}
	Vec2 operator-(const Point2& point2) const {
		return Vec2(x - point2.x, y - point2.y);
	}
	auto operator<=>(const Point2& other) const = default;
};
using FloatPoint2 = Point2<f32>;
using IntPoint2 = Point2<i32>;
using UIntPoint2 = Point2<u32>;