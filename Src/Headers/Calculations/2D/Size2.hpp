#pragma once
#include <GLAD/glad.h>
#include <concepts>
#include <type_traits>
#include <cmath>
#include <optional>
#include "Calculations/General/Types.hpp"
#include <cassert>
#include <string>
template <typename Type>
class Size2 {
public:
	Type width = {};
	Type height = {};
	Size2() = default;
	Size2(const Size2& other) = default;
	Size2(Size2&& other) noexcept = default;
	Size2& operator=(const Size2& other) = default;
	Size2& operator=(Size2&& other) noexcept = default;
	Size2(Type width, Type height) : width(width), height(height) {
		assert(width >= 0 && "Size2::Size2: width cannot be negative");
		assert(height >= 0 && "Size2::Size2: height cannot be negative");
	}
	Size2(Type value) : width(value), height(value) {
		assert(width >= 0 && "Size2::Size2: width cannot be negative");
		assert(height >= 0 && "Size2::Size2: height cannot be negative");
	}
	template <typename MultiplierType>
	requires std::is_arithmetic_v<MultiplierType>
	Size2& scaleUp(MultiplierType multiplier) {
		width= static_cast<Type>(width * multiplier);
		height = static_cast<Type>(height * multiplier);
		assert(width >= 0 && "Size2::scaleUp: scaling up caused width to become negative");
		assert(height >= 0 && "Size2::scaleUp: scaling up caused height to become negative");
		return *this;
	}
	template <typename MultiplierType>
	requires std::is_arithmetic_v<MultiplierType>
	Size2& scaleDown(MultiplierType multiplier) {
		width= static_cast<Type>(width/ multiplier);
		height = static_cast<Type>(height / multiplier);
		assert(width >= 0 && "Size2::scaleDown: scaling down caused width to become negative");
		assert(height >= 0 && "Size2::scaleDown: scaling down caused height to become negative");
		return *this;
	}
	template <typename AmountType>
	requires std::is_arithmetic_v<AmountType>
	Size2& makeWider(AmountType amount) {
		width += amount;
		assert(width >= 0 && "Size2::makeWider: change of width caused width to become negative");
		return *this;
	}
	template <typename AmountType>
	requires std::is_arithmetic_v<AmountType>
	Size2& makeThinner(AmountType amount) {
		width -= amount;
		assert(width >= 0 && "Size2::makeThinner: change of width caused width to become negative");
		return *this;
	}
	template <typename AmountType>
	requires std::is_arithmetic_v<AmountType>
	Size2& makeLonger(AmountType amount) {
		height += amount;
		assert(height >= 0 && "Size2::makeLonger: change of height caused height to become negative");
	}
	template <typename AmountType>
	requires std::is_arithmetic_v<AmountType>
	Size2& makeShorter(AmountType amount) {
		height -= amount;
		assert(height >= 0 && "Size2::makeLonger: change of height caused height to become negative");
	}
	boolean isZero() const {
		return width == 0 || height == 0;
	}
	boolean isValid() const {
		return width >= 0 && height >= 0;
	}
	boolean isPositive() const {
		return width > 0 && height > 0;
	}
	boolean isNonZero() const {
		return width != 0 && height != 0;
	}
	Type area() const {
		return width * height;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Size2 operator+(ValueType value) const {
		assert(width + value >= 0 && "Size2::operator+: addition caused width to be negative");
		assert(height + value >= 0 && "Size2::operator+: addition caused height to be negative");
		return Size2(width + value, height + value);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Size2 operator-(ValueType value) const {
		assert(width - value >= 0 && "Size2::operator-: subtration caused width to be negative");
		assert(height - value >= 0 && "Size2::operator-: subtraction caused height to be negative");
		return Size2(width - value, height - value);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Size2 operator*(ValueType value) const {
		assert(width * value >= 0 && "Size2::operator*: multiplication caused width to be negative");
		assert(height * value >= 0 && "Size2::operator*: multiplication caused height to be negative");
		return Size2(width * value, height * value);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Size2 operator/(ValueType value) const {
		assert(width / value >= 0 && "Size2::operator+: division caused width to be negative");
		assert(height / value >= 0 && "Size2::operator+: division caused height to be negative");
		return Size2(width / value, height / value);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	friend Size2 operator+(ValueType value, const Size2& size2) {
		assert(size2.width + value >= 0 && "Size2::operator+: addition caused width to be negative");
		assert(size2.height + value >= 0 && "Size2::operator+: addition caused height to be negative");
		return Size2(size2.width + value, size2.height + value);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	friend Size2 operator*(ValueType value, const Size2& size2) {
		assert(size2.width * value >= 0 && "Size2::operator*: multiplication caused width to be negative");
		assert(size2.height * value >= 0 && "Size2::operator*: multiplication caused height to be negative");
		return Size2(size2.width * value, size2.height * value);
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Size2& operator+=(ValueType value) {
		width += value;
		height += value;
		assert(width >= 0 && "Size2::operator+=: addition caused width to be negative");
		assert(height >= 0 && "Size2::operator+=: addition caused height to be negative");
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Size2& operator-=(ValueType value) {
		width -= value;
		height -= value;
		assert(width >= 0 && "Size2::operator-=: subtraction caused width to be negative");
		assert(height >= 0 && "Size2::operator-=: subtraction caused height to be negative");
		return *this;
	}
	template <typename ValueType>
	requires std::is_arithmetic_v<ValueType>
	Size2& operator*=(ValueType value) {
		width *= value;
		height *= value;
		assert(width >= 0 && "Size2::operator*=: multiplication caused width to be negative");
		assert(height >= 0 && "Size2::operator*=: multiplication caused height to be negative");
		return *this;
	}
	template <typename ValueType>
		requires std::is_arithmetic_v<ValueType>
	Size2& operator/=(ValueType value) {
		width /= value;
		height /= value;
		assert(width >= 0 && "Size2::operator/=: division caused width to be negative");
		assert(height >= 0 && "Size2::operator/=: division caused height to be negative");
		return *this;
	}

};

using IntSize2 = Size2<i32>;
using UIntSize2 = Size2<u32>;
using FloatSize2 = Size2<f32>;