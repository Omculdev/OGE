#pragma once
#include <Calculations/2D/Vector2.hpp>
#include "Calculations/General/Types.hpp"
template <typename Type>
requires std::is_arithmetic_v<Type>
class Vector3 {
public:
	Type x = {};
	Type y = {};
	Type z = {};
	Vector3() = default;
	Vector3(const Vector3& other) = default;
	Vector3(Vector3&& other) noexcept = default;
	Vector3& operator=(const Vector3& other) = default;
	Vector3& operator=(Vector3&& other) noexcept = default;
	~Vector3() = default;
	Vector3(const Vector2<Type>& vec2, Type value) : x(vec2.x), y(vec2.y), z(value) {}
	Vector3(Type x, Type y, Type z) : x(x), y(y), z(z) {}
	explicit Vector3(Type value) : x(value), y(value), z(value) {}
	Vector3 operator+(const Vector3& other) const {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 operator-(const Vector3& other) const {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	Vector3 operator*(const Vector3& other) const {
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	Vector3 operator/(const Vector3& other) const {
		return Vector3(x / other.x, y / other.y, z / other.z);
	}
	Vector3& operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3& operator-=(const Vector3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3& operator*=(const Vector3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	Vector3& operator/=(const Vector3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	auto operator<=>(const Vector3& other) const = default;
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3 operator+(const ScalarType& scalar) const {
		return Vector3(x + scalar, y + scalar, z + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3 operator-(const ScalarType& scalar) const {
		return Vector3(x - scalar, y - scalar, z - scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3 operator*(const ScalarType& scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3 operator/(const ScalarType& scalar) const {
		return Vector3(x / scalar, y / scalar, z / scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3& operator+=(const ScalarType& scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3& operator-=(const ScalarType& scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3& operator*=(const ScalarType& scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vector3& operator/=(const ScalarType& scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vector3 operator+(const ScalarType& scalar, const Vector3& vec3) {
		return Vector3(vec3.x + scalar, vec3.y + scalar, vec3.z + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vector3 operator*(const ScalarType& scalar, const Vector3& vec3) {
		return Vector3(vec3.x * scalar, vec3.y * scalar, vec3.z * scalar);
	}
	static inline double dotProduct(const Vector3& first, const Vector3& second) {
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}
	inline double length() const {
		return std::sqrt(x * x + y * y + z * z);
	}
	static inline double distance(const Vector3& first, const Vector3& second) {
		return (first - second).length();
	}
	inline double lengthSquared() const {
		return x * x + y * y + z * z;
	}
	inline void normalize() {
		double length = this->length();
		if (length > 0) {
			*this /= length;
		}
	}
	inline std::optional<Vector3> normalized() const {
		double length = this->length();
		if (length > 0) {
			return *this / length;
		}
		return std::nullopt;
	}

};
using IntVector3 = Vector3<i32>;
using FloatVector3 = Vector3<f32>;
using UIntVector3 = Vector3<u32>;