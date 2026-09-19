#pragma once
#include "Calculations/General/Types.hpp"
#include <GLAD/glad.h>
#include <concepts>
#include <type_traits>
#include <cmath>
#include <optional>
template <typename Vec2Type>
requires std::is_arithmetic_v<Vec2Type>
class Vec2;
template <typename Type>
requires std::is_arithmetic_v<Type>
class Point2 {
public:
	Type x = {};
	Type y = {};
	Point2() = default;
	Point2(const Point2<Type>& other) = default;
	Point2(Point2<Type>&& other) noexcept = default;
	Point2<Type>& operator=(const Point2<Type>& other) = default;
	Point2<Type>& operator=(Point2<Type>&& other) noexcept = default;
	~Point2() = default;
	Point2(Type x, Type y) : x(x), y(y) {}
	explicit Point2(Type value) : x(value), y(value) {}
	Point2<Type> operator+(const Vec2<Type>& vec2) const {
		return Point2<Type>(x + vec2.x, y + vec2.y);
	}
	Point2<Type> operator-(const Vec2<Type>& vec2) const {
		return Point2<Type>(x - vec2.x, y - vec2.y);
	}
	Vec2<Type> operator-(const Point2<Type>& point2) const {
		return Vec2<Type>(x - point2.x, y - point2.y);
	}
	auto operator<=>(const Point2<Type>& other) const = default;
};
using FloatPoint2 = Point2<f32>;
using IntPoint2 = Point2<i32>;
using UIntPoint2 = Point2<u32>;