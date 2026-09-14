#pragma once
#include "Calculations/2D/RectBounds.hpp"
#include "Calculations/2D/Point2.hpp"
#include "Calculations/General/Color.hpp"
#include <GLM/glm.hpp>
template <typename Type>
class Shape2D {
public:
	virtual ~Shape2D() = default;
	virtual void setPosition(const Point2<Type>& position) = 0;
	virtual void setPosition(Type positionX, Type positionY) = 0;
	virtual void setColor(const Color& color) = 0;
	virtual void setColor(Type r, Type g, Type b, Type a = 255) = 0;
	virtual void setSize(const Size2<Type>& size) = 0;
	virtual bool contains(const Point2<Type>& point) = 0;
	virtual bool intersects(const Shape2D<Type>& shape) = 0;
	virtual Point2<Type> getPosition() const = 0;
	virtual Size2<Type> getSize() const = 0;
	virtual Color getColor() const = 0;
};