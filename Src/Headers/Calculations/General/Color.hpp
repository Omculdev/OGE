#pragma once
#include "Calculations/General/Types.hpp"
#include <GLAD/glad.h>
#include <concepts>
#include <type_traits>
#include <algorithm>
class Color {
public:
	u8 r = {};
	u8 g = {};
	u8 b = {};
	u8 a = {};
	Color() = default;
	Color(const Color& other) = default;
	Color(Color&& other) noexcept = default;
	Color& operator=(const Color& other) = default;
	Color& operator=(Color&& other) noexcept = default;
	~Color() = default;
	Color(u8 red, u8 green, u8 blue, u8 alpha = 255);
	explicit Color(u32 hexvalue);
	Color operator+(const Color& other) const;
	Color operator-(const Color& other) const;
	Color operator*(const Color& other) const;
	Color operator/(const Color& other) const;
	Color& operator+=(const Color& other);
	Color& operator-=(const Color& other);
	Color& operator*=(const Color& other);
	Color& operator/=(const Color& other);
	auto operator<=>(const Color& other) const = default;
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color operator+(const ValueType& value) const {
		return Color(
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) + value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) + value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) + value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) + value, 0, 255))
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color operator-(const ValueType& value) const {
		return Color(
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) - value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) - value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) - value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) - value, 0, 255))
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color operator*(const ValueType& value) const {
		return Color(
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) * value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) * value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) * value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) * value, 0, 255))
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color operator/(const ValueType& value) const {
		return Color(
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) / value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) / value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) / value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) / value, 0, 255))
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color& operator+=(const ValueType& value) {
		r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) + value, 0, 255));
		g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) + value, 0, 255));
		b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) + value, 0, 255));
		a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) + value, 0, 255));
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color& operator-=(const ValueType& value) {
		r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) - value, 0, 255));
		g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) - value, 0, 255));
		b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) - value, 0, 255));
		a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) - value, 0, 255));
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color& operator*=(const ValueType& value) {
		r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) * value, 0, 255));
		g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) * value, 0, 255));
		b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) * value, 0, 255));
		a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) * value, 0, 255));
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Color& operator/=(const ValueType& value) {
		r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) / value, 0, 255));
		g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) / value, 0, 255));
		b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) / value, 0, 255));
		a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) / value, 0, 255));
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	friend Color operator+(const ValueType& value, const Color& color) {
		return Color(
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.r) + value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.g) + value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.b) + value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.a) + value, 0, 255))
		);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	friend Color operator*(const ValueType& value, const Color& color) {
		return Color(
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.r) * value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.g) * value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.b) * value, 0, 255)),
			static_cast<u8>(std::clamp<u16>(static_cast<u16>(color.a) * value, 0, 255))
		);
	}
};