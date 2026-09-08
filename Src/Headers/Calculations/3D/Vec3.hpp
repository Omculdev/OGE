#pragma once
#include <Calculations/2D/Vec2.hpp>
#include "Calculations/General/Types.hpp"
template <typename Type>
requires std::is_arithmetic_v<Type>
class Vec3 {
public:
	Type x = {};
	Type y = {};
	Type z = {};
	Vec3() = default;
	Vec3(const Vec3& other) = default;
	Vec3(Vec3&& other) noexcept = default;
	Vec3& operator=(const Vec3& other) = default;
	Vec3& operator=(Vec3&& other) noexcept = default;
	~Vec3() = default;
	Vec3(const Vec2<Type>& vec2, Type value) : x(vec2.x), y(vec2.y), z(value) {}
	Vec3(Type x, Type y, Type z) : x(x), y(y), z(z) {}
	explicit Vec3(Type value) : x(value), y(value), z(value) {}
	Vec3 operator+(const Vec3& other) const {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}
	Vec3 operator-(const Vec3& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}
	Vec3 operator*(const Vec3& other) const {
		return Vec3(x * other.x, y * other.y, z * other.z);
	}
	Vec3 operator/(const Vec3& other) const {
		return Vec3(x / other.x, y / other.y, z / other.z);
	}
	Vec3& operator+=(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vec3& operator*=(const Vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	Vec3& operator/=(const Vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	auto operator<=>(const Vec3& other) const = default;
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3 operator+(const ScalarType& scalar) const {
		return Vec3(x + scalar, y + scalar, z + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3 operator-(const ScalarType& scalar) const {
		return Vec3(x - scalar, y - scalar, z - scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3 operator*(const ScalarType& scalar) const {
		return Vec3(x * scalar, y * scalar, z * scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3 operator/(const ScalarType& scalar) const {
		return Vec3(x / scalar, y / scalar, z / scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3& operator+=(const ScalarType& scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3& operator-=(const ScalarType& scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3& operator*=(const ScalarType& scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	Vec3& operator/=(const ScalarType& scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vec3 operator+(const ScalarType& scalar, const Vec3& vec3) {
		return Vec3(vec3.x + scalar, vec3.y + scalar, vec3.z + scalar);
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	friend Vec3 operator*(const ScalarType& scalar, const Vec3& vec3) {
		return Vec3(vec3.x * scalar, vec3.y * scalar, vec3.z * scalar);
	}
	static inline double dotProduct(const Vec3& first, const Vec3& second) {
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}
	inline double length() const {
		return std::sqrt(x * x + y * y + z * z);
	}
	static inline double distance(const Vec3& first, const Vec3& second) {
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
	inline std::optional<Vec3> normalized() const {
		double length = this->length();
		if (length > 0) {
			return *this / length;
		}
		return std::nullopt;
	}

};
using IntVec3 = Vec3<i32>;
using FloatVec3 = Vec3<f32>;
using UIntVec3 = Vec3<u32>;