#pragma once
#include "Shape2D.hpp"
template<typename Type>
requires std::is_arithmetic_v<Type>
class Rectangle : public Shape2D<Type> {
private:
	RectBounds<Type> bounds = {};
	glm::mat4 transform = glm::mat4(1.0f);
	Color color = {};
public:
	Rectangle() = default;
	Rectangle(const Rectangle& other) = default;
	Rectangle(Rectangle&& other) noexcept = default;

	Rectangle& operator=(const Rectangle& other) = default;
	Rectangle& operator=(Rectangle&& other) noexcept = default;
	Rectangle(const Size2<Type>& size, const Point2<Type>& position = Point2<Type>(0,0), const Color& color = Color(255, 255, 255, 255)) :
		bounds.position(position),
		bounds.size(size),
		color(color)
	{}
	Rectangle(Type sizeX, Type sizeY, const Point2<Type>& position = Point2<Type>(0,0), const Color& color = Color(255, 255, 255, 255)) :
		bounds.size(Size2(sizeX, sizeY)),
		bounds.position(position),
		color(color)
	{}
	Rectangle(Type sizeX, Type sizeY, Type positionX = 0, Type positionY = 0, const Color& color = Color(255, 255, 255, 255)) :
		bounds.size(Size2(sizeX, sizeY)),
		bounds.position(Point2(positionX, positionY)),
		color(color)
	{}
	Rectangle(Type sizeX, Type sizeY, Type positionX = 0, Type positionY = 0, u8 r, u8 g, u8 b, u8 a) :
		bounds.size(Size2(sizeX, sizeY)),
		bounds.position(Point2(positionX, positionY)),
		color(Color(r,g,b,a))
	{}
	void setPosition(const Point2<Type>& position) override {
		bounds.position = position;
	}
	void setPosition(Type positionX, Type positionY) override {
		bounds.position = Point2<Type>(positionX, positionY);
	}
	void setColor(const Color& color) override {
		this->color = color;
	}
	void setColor(Type r, Type g, Type b, Type a = 255) override {
		color = Color(r, g, b, a);
	}
	void setSize(const Size2<Type>& size) override {
		bounds.size = size;
	}
	bool contains(const Point2<Type>& point) const override {
		return bounds.contains(point);
	}
	bool intersects(const Shape2D<Type>& other) const override {
		const Rectangle* rectptr = dynamic_cast<const Rectangle*>(&other);
		if (rectptr) {
			return bounds.intersects(*rectptr);
		}
		return false;
	}
	std::optional<RectBounds<Type>> getIntersection(const Rectangle<Type>& other) const {
		return bounds.getIntersection(other);
	}
	[[nodiscard]] Point2<Type> getPosition() const override {
		return bounds.position;
	}
	[[nodiscard]] Size2<Type> getSize() const override {
		return bounds.size;
	}
	Color getColor() const override {
		return color;
	}
};
using FloatRectangle = Rectangle<f32>;
using IntRectangle = Rectangle<i32>;
using UIntRectangle = Rectangle<u32>;