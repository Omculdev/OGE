#pragma once
#include "Calculations/2D/RectBounds.hpp"
#include "Calculations/2D/Point2.hpp"
#include "Calculations/General/Color.hpp"
#include <GLM/glm.hpp>
#include <optional>
template <typename Type>
class Shape2D {
public:
	virtual ~Shape2D() = default;
	virtual void setPosition(const Point2<Type>& position) = 0;
	virtual void setPosition(Type positionX, Type positionY) = 0;
	virtual void setFillColor(const Color& color) = 0;
	virtual void setFillColor(u8 r, u8 g, u8 b, u8 a = 255) = 0;
	virtual void setSize(const Size2<Type>& size) = 0;
	virtual boolean contains(const Point2<Type>& point) const = 0;
	virtual boolean intersects(const Shape2D<Type>& shape) const = 0;
	virtual boolean isSolidColor() const = 0;
	virtual Point2<Type> getPosition() const = 0;
	virtual Size2<Type> getSize() const = 0;
	virtual std::optional<Color> getFillColor() const = 0;
};