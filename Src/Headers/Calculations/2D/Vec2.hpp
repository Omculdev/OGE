#pragma once
#include <GLAD/glad.h>
#include <concepts>
#include <type_traits>
#include <cmath>
#include <optional>
#include <Calculations/General/Types.hpp>
#include <Calculations/2D/Point2.hpp>
template <typename Type>
requires std::is_arithmetic_v<Type>
class Vec2 {
public:
	Type x = {};
	Type y = {};
	Vec2() = default;
	Vec2(const Vec2& other) = default;
	Vec2(Vec2&& other) noexcept = default;
	Vec2& operator=(const Vec2& other) = default;
	Vec2& operator=(Vec2&& other) noexcept = default;
	~Vec2() = default;
	Vec2(Type x, Type y) : x(x), y(y) {}
	Vec2(const Point2& start, const Point2& end) : x(end.x - start.x), y(end.y - start.y) {}
	Vec2(const Point2& start, Type endX, Type endY) : x(endX-start.x), y(endY - start.y) {}
	Vec2(Type startX, Type startY, const Point2& end) : x(end.x - startX), y(end.x - startY) {}
	Vec2(Type startX, Type startY, Type endX, Type endY) : x(endX-startX), y(endY - startY) {}
	explicit Vec2(Type value) : x(value), y(value) {}
	Vec2 operator+(const Vec2& other) const {
		return Vec2(x + other.x, y + other.y);
	}
	Vec2 operator-(const Vec2& other) const {
		return Vec2(x - other.x, y - other.y);
	}
	Vec2 operator*(const Vec2& other) const {
		return Vec2(x * other.x, y * other.y);
	}
	Vec2 operator/(const Vec2& other) const {
		return Vec2(x / other.x, y / other.y);
	}
	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vec2& operator*=(const Vec2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}
	Vec2& operator/=(const Vec2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}
	auto operator<=>(const Vec2& other) const = default;
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2 operator+(const ScalarType& scalar) const {
		return Vec2(x + scalar, y + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2 operator-(const ScalarType& scalar) const {
		return Vec2(x - scalar, y - scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2 operator*(const ScalarType& scalar) const {
		return Vec2(x * scalar, y * scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2 operator/(const ScalarType& scalar) const {
		return Vec2(x / scalar, y / scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2& operator+=(const ScalarType& scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2& operator-=(const ScalarType& scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2& operator*=(const ScalarType& scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec2& operator/=(const ScalarType& scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vec2 operator+(const ScalarType& scalar, const Vec2& vec2) {
		return Vec2(vec2.x + scalar, vec2.y + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vec2 operator*(const ScalarType& scalar, const Vec2& vec2) {
		return Vec2(vec2.x * scalar, vec2.y * scalar);
	}
	static inline f64 dotProduct(const Vec2& first, const Vec2& second) {
		return first.x * second.x + first.y * second.y;
	}
	static inline f64 crossProduct(const Vec2& first, const Vec2& second) {
		return first.x * second.y - first.y * second.x;
	}
	inline f64 length() const {
		return std::sqrt(x * x + y * y);
	}
	static inline f64 distance(const Vec2& first, const Vec2& second) {
		return (first - second).length();
	}
	inline f64 lengthSquared() const {
		return x * x + y * y;
	}
	inline void normalize() {
		f64 length = this->length();
		if (length > 0) {
			*this /= length;
		}
	}
	inline std::optional<Vec2> normalized() const {
		f64 length = this->length();
		if (length > 0) {
			return *this / length;
		}
		return std::nullopt;
	}

};
using IntVec2 = Vec2<i32>;
using FloatVec2 = Vec2<f32>;
using UIntVec2 = Vec2<u32>;