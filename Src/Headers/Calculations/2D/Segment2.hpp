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
template <typename Point2Type>
requires std::is_arithmetic_v<Point2Type>
class Point2;
template <typename Type>
requires std::is_arithmetic_v<Type>
class Segment2 {
public:
	Point2<Type> start = {};
	Point2<Type> end = {};
	Segment2() = default;
	Segment2(const Segment2<Type>& other) = default;
	Segment2(Segment2<Type>&& other) noexcept = default;
	Segment2& operator=(const Segment2<Type>& other) = default;
	Segment2& operator=(Segment2<Type>&& other) noexcept = default;
	~Segment2() = default;
	Segment2(const Point2<Type>& start, const Point2<Type>& end) : start(start), end(end) {}
	Segment2(const Point2<Type>& start, Type endX, Type endY) : start(start), end(Point2<Type>(endX, endY)) {}
	Segment2(Type startX, Type startY, const Point2<Type>& end) : start(Point2<Type>(startX, startY)), end(end) {}
	Segment2(Type startX, Type startY, Type endX, Type endY) : start(Point2<Type>(startX, startY)), end(Point2<Type>(endX, endY)) {}
	auto operator<=>(const Segment2<Type>& other) const = default;
	Segment2<Type> operator+(const Segment2<Type>& other) const {
		return Segment2<Type>(
			Point2<Type>(start.x + other.start.x, start.y + other.start.y),
			Point2<Type>(end.x + other.end.x, end.y + other.end.y)
		);
	}
	Segment2<Type> operator-(const Segment2<Type>& other) const {
		return Segment2<Type>(
			Point2<Type>(start.x - other.start.x, start.y - other.start.y),
			Point2<Type>(end.x - other.end.x, end.y - other.end.y)
		);
	}
	Segment2<Type> operator*(const Segment2<Type>& other) const {
		return Segment2<Type>(
			Point2<Type>(start.x * other.start.x, start.y * other.start.y),
			Point2<Type>(end.x * other.end.x, end.y * other.end.y)
		);
	}
	Segment2<Type> operator/(const Segment2<Type>& other) const {
		return Segment2<Type>(
			Point2<Type>(start.x / other.start.x, start.y / other.start.y),
			Point2<Type>(end.x / other.end.x, end.y / other.end.y)
		);
	}
	Segment2<Type>& operator+=(const Segment2<Type>& other) {
		start.x += other.start.x;
		start.y += other.start.y;
		end.x += other.end.x;
		end.y += other.end.y;
		return *this;
	}
	Segment2<Type>& operator-=(const Segment2<Type>& other) {
		start.x -= other.start.x;
		start.y -= other.start.y;
		end.x -= other.end.x;
		end.y -= other.end.y;
		return *this;
	}
	Segment2<Type>& operator*=(const Segment2<Type>& other) {
		start.x *= other.start.x;
		start.y *= other.start.y;
		end.x *= other.end.x;
		end.y *= other.end.y;
		return *this;
	}
	Segment2<Type>& operator/=(const Segment2<Type>& other) {
		start.x /= other.start.x;
		start.y /= other.start.y;
		end.x /= other.end.x;
		end.y /= other.end.y;
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type> operator+(ValueType value) const {
		return Segment2<Type>(
			Point2<Type>(start.x + value, start.y + value),
			Point2<Type>(end.x + value, end.y + value)
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type> operator-(ValueType value) const {
		return Segment2<Type>(
			Point2<Type>(start.x - value, start.y - value),
			Point2<Type>(end.x - value, end.y - value)
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type> operator*(ValueType value) const {
		return Segment2<Type>(
			Point2<Type>(start.x * value, start.y * value),
			Point2<Type>(end.x * value, end.y * value)
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type> operator/(ValueType value) const {
		return Segment2<Type>(
			Point2<Type>(start.x / value, start.y / value),
			Point2<Type>(end.x / value, end.y / value)
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type>& operator+=(ValueType value) {
		start.x += value;
		start.y += value;
		end.x += value;
		end.y += value;
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type>& operator-=(ValueType value) {
		start.x -= value;
		start.y -= value;
		end.x -= value;
		end.y -= value;
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type>& operator*=(ValueType value) {
		start.x *= value;
		start.y *= value;
		end.x *= value;
		end.y *= value;
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type>& operator/=(ValueType value) {
		start.x /= value;
		start.y /= value;
		end.x /= value;
		end.y /= value;
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type>& shiftX(ValueType value) {
		start.x += value;
		end.x += value;
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Segment2<Type>& shiftY(ValueType value) {
		start.y += value;
		end.y += value;
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Point2<Type> center() const {
		return Point2<Type>((end.x + start.x) / 2, (end.y + start.y) / 2);
	}
	f64 length() const {
		return std::sqrt(((end.x - start.x) * (end.x - start.x)) + ((end.y - start.y) * (end.y - start.y)));
	}
	f64 lengthSquared() const {
		return ((end.x - start.x) * (end.x - start.x)) + ((end.y - start.y) * (end.y - start.y));
	}
	boolean contains(const Point2<Type>& point, Type epsilon = 1e-12) const {
		Vec2<Type> SE(start, end);
		Vec2<Type> SP(start, point);
		f64 crossproduct = Vec2<Type>::crossProduct(SE, SP);
		f64 dotproduct = Vec2<Type>::dotProduct(SE, SP);
		if (std::abs(crossproduct) <= epsilon && dotproduct >= 0 && dotproduct <= lengthSquared()) {
			return true;
		}
		return false;
	}
};
using IntSegment2 = Segment2<i32>;
using FloatSegment2 = Segment2<f32>;
using UIntSegment2 = Segment2<u32>;