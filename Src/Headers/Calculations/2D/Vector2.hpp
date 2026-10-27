#pragma once
#include <GLAD/glad.h>
#include <concepts>
#include <type_traits>
#include <cmath>
#include <optional>
#include <Calculations/General/Types.hpp>
template <typename Point2Type>
requires std::is_arithmetic_v<Point2Type>
class Point2;
template <typename Type>
requires std::is_arithmetic_v<Type>
class Vector2 {
public:
	Type x = {};
	Type y = {};
	Vector2() = default;
	Vector2(const Vector2<Type>& other) = default;
	Vector2(Vector2&& other) noexcept = default;
	Vector2& operator=(const Vector2<Type>& other) = default;
	Vector2& operator=(Vector2<Type>&& other) noexcept = default;
	~Vector2() = default;
	Vector2(Type x, Type y) : x(x), y(y) {}
	Vector2(const Point2<Type>& start, const Point2<Type>& end) : x(end.x - start.x), y(end.y - start.y) {}
	Vector2(const Point2<Type>& start, Type endX, Type endY) : x(endX-start.x), y(endY - start.y) {}
	Vector2(Type startX, Type startY, const Point2<Type>& end) : x(end.x - startX), y(end.x - startY) {}
	Vector2(Type startX, Type startY, Type endX, Type endY) : x(endX-startX), y(endY - startY) {}
	explicit Vector2(Type value) : x(value), y(value) {}
	Vector2<Type> operator+(const Vector2<Type>& other) const {
		return Vector2<Type>(x + other.x, y + other.y);
	}
	Vector2<Type> operator-(const Vector2<Type>& other) const {
		return Vector2(x - other.x, y - other.y);
	}
	Vector2<Type> operator*(const Vector2<Type>& other) const {
		return Vector2<Type>(x * other.x, y * other.y);
	}
	Vector2<Type> operator/(const Vector2<Type>& other) const {
		return Vector2<Type>(x / other.x, y / other.y);
	}
	Vector2<Type>& operator+=(const Vector2<Type>& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2<Type>& operator-=(const Vector2<Type>& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2<Type>& operator*=(const Vector2<Type>& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}
	Vector2<Type>& operator/=(const Vector2<Type>& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}
	auto operator<=>(const Vector2<Type>& other) const = default;
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type> operator+(const ScalarType& scalar) const {
		return Vector2<Type>(x + scalar, y + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type> operator-(const ScalarType& scalar) const {
		return Vector2<Type>(x - scalar, y - scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type> operator*(const ScalarType& scalar) const {
		return Vector2<Type>(x * scalar, y * scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type> operator/(const ScalarType& scalar) const {
		return Vector2<Type>(x / scalar, y / scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type>& operator+=(const ScalarType& scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type>& operator-=(const ScalarType& scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type>& operator*=(const ScalarType& scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector2<Type>& operator/=(const ScalarType& scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vector2<Type> operator+(const ScalarType& scalar, const Vector2<Type>& vec2) {
		return Vector2<Type>(vec2.x + scalar, vec2.y + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vector2<Type> operator*(const ScalarType& scalar, const Vector2<Type>& vec2) {
		return Vector2<Type>(vec2.x * scalar, vec2.y * scalar);
	}
	static inline f64 dotProduct(const Vector2<Type>& first, const Vector2<Type>& second) {
		return first.x * second.x + first.y * second.y;
	}
	static inline f64 crossProduct(const Vector2<Type>& first, const Vector2<Type>& second) {
		return first.x * second.y - first.y * second.x;
	}
	inline f64 length() const {
		return std::sqrt(x * x + y * y);
	}
	static inline f64 distance(const Vector2<Type>& first, const Vector2<Type>& second) {
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
	inline std::optional<Vector2<Type>> normalized() const {
		f64 length = this->length();
		if (length > 0) {
			return *this / length;
		}
		return std::nullopt;
	}

};
using IntVector2 = Vector2<i32>;
using FloatVector2 = Vector2<f32>;
using UIntVector2 = Vector2<u32>;