#pragma once
#include "Calculations/General/Types.hpp"
#include <Calculations/2D/Point2.hpp>
#include <Calculations/2D/Segment2.hpp>
#include <Calculations/2D/Size2.hpp>
#include <algorithm>
#include <optional>
template <typename Type>
class RectBounds {
public:
	Point2<Type> position;
	Size2<Type> size;
	RectBounds() = default;
	RectBounds(const RectBounds& other) = default;
	RectBounds(RectBounds&& other) noexcept = default;
	RectBounds& operator=(const RectBounds& other) = default;
	RectBounds& operator=(RectBounds&& other) noexcept = default;
	~RectBounds() = default;
	RectBounds(const Point2<Type>& position, const Size2<Type>& size) : position(position), size(size) {}
	RectBounds(Type positionX, Type positionY, const Size2<Type>& size) : position(Point2<Type>(positionX, positionY)), size(size) {}
	RectBounds(const Point2<Type>& position, Type width, Type height) : position(position), size(Size2<Type>(width, height)) {}
	RectBounds(Type positionX, Type positionY, Type width, Type height) : position(Point2<Type>(positionX, positionY)), size(Size2<Type>(width, height)) {}
	Point2<Type> topLeft() const {
		return Point2<Type>(
			position.x - size.width / 2,
			position.y + size.height / 2
		);
	}
	Point2<Type> topRight() const {
		return Point2<Type>(
			position.x + size.width / 2,
			position.y + size.height / 2
		);
	}
	Point2<Type> bottomLeft() const {
		return Point2<Type>(
			position.x - size.width / 2,
			position.y - size.height / 2
		);
	}
	Point2<Type> bottomRight() const {
		return Point2<Type>(
			position.x + size.width / 2,
			position.y - size.height / 2
		);
	}
	Segment2<Type> left() const {
		return Segment2(bottomLeft(), topLeft());
	}
	Segment2<Type> right() const {
		return Segment2(bottomRight(), topRight());
	}
	Segment2<Type> top() const {
		return Segment2(topRight(), topLeft());
	}
	Segment2<Type> bottom() const {
		return Segment2(bottomRight(), bottomLeft());
	}
	boolean intersects(const RectBounds<Type>& other) const {
		return (!(
			((topLeft().y < other.bottomLeft().y && topRight().y < other.bottomRight().y) ||
				(bottomLeft().y > other.topLeft().y && bottomRight().y > other.topRight().y)) &&
			((topLeft().x > other.topRight().x && bottomLeft().x > other.bottomRight().x) ||
				(topRight().x < other.topLeft().x && bottomRight().x < other.bottomLeft().x))
			));
	}
	std::optional<RectBounds> getIntersection(const RectBounds<Type>& other) const {
		if (
			((topLeft().y < other.bottomLeft().y && topRight().y < other.bottomRight().y) ||
				(bottomLeft().y > other.topLeft().y && bottomRight().y > other.topRight().y)) &&
			((topLeft().x > other.topRight().x && bottomLeft().x > other.bottomRight().x) ||
				(topRight().x < other.topLeft().x && bottomRight().x < other.bottomLeft().x))
			) {
			return std::nullopt;
		}
		Type left = std::max<Type>(topLeft().x, other.topLeft().x);
		Type right = std::min<Type>(topRight().x, other.topRight().x);
		Type top = std::min<Type>(topLeft().y, other.topLeft().y);
		Type bottom = std::max<Type>(bottomLeft().y, other.bottomLeft().y);
		RectBounds intersection = {};
		intersection.size.width = right - left;
		intersection.size.height = top - bottom;
		intersection.position = Point2<Type>(
			left + intersection.size.width / 2,
			top - intersection.size.height / 2
		);
		return intersection;
	}
	boolean contains(const Point2<Type>& point) const {
		return point.x >= topLeft().x && point.x <= topRight().x &&
			point.y >= bottomLeft().y && point.y <= topLeft().y;
	}

};
using IntRectBounds = RectBounds<i32>;
using FloatRectBounds = RectBounds<f32>;
using UIntRectBounds = RectBounds<u32>;