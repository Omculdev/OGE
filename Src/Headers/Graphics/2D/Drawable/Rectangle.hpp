#pragma once
#include "Shape2D.hpp"
#include "Utils/Enums/RectangleVertices.hpp"
#include "Utils/Rendering/VideoMemory/Vertex.hpp"
#include <Calculations/2D/Point2.hpp>
#include <Calculations/2D/RectBounds.hpp>
#include <Calculations/2D/Size2.hpp>
#include <Calculations/General/Color.hpp>
#include <Calculations/General/Types.hpp>
#include <GLM/fwd.hpp>
#include <algorithm>
#include <array>
#include <optional>
#include <type_traits>
#include "Utils/Calculations/MathUtils.hpp"
template<typename Type>
requires std::is_arithmetic_v<Type>
class Rectangle : public Shape2D<Type> {
private:
	glm::mat4 transform = glm::mat4(1.0f);
	std::array<Color, std::to_underlying(RectangleVertex::amount)> vertex_color;
	RectBounds<Type> bounds = {};
public:
	Rectangle() {}
	Rectangle(const Rectangle& other) :
		Shape2D<Type>(std::nullopt, false),
		bounds(other.bounds),
		transform(other.transform),
		vertex_color(other.vertex_color)
	{}
	Rectangle& operator=(const Rectangle& other) {
		if (this == &other) return *this;
		Shape2D<Type>::operator=(other);
		bounds = other.bounds;
		transform = other.transform;
		vertex_color = other.vertex_color;
		return *this;
	}
	Rectangle(Rectangle&& other) noexcept  :
		Shape2D<Type>(std::move(other)),
		bounds(std::move(other.bounds)),
		transform(std::move(other.transform)),
		vertex_color(std::move(other.vertex_color))
	{
		other.draw_id = std::nullopt;
	}
	Rectangle& operator=(Rectangle&& other) noexcept {
		if (this == &other) return *this;
		Shape2D<Type>::operator=(std::move(other));
		bounds = std::move(other.bounds);
		transform = std::move(other.transform);
		vertex_color = std::move(other.vertex_color);
		other.draw_id = std::nullopt;
		return *this;
	}
	Rectangle(
		const Size2<Type>& size,
		const Point2<Type>& position = Point2<Type>(0, 0),
		const Color& color = Color(255, 255, 255, 255)
	) :
		bounds(position, size),
		vertex_color{ color, color, color, color }
	{}
	Rectangle(
		Type sizeX, Type sizeY,
		const Point2<Type>& position = Point2<Type>(0, 0),
		const Color& color = Color(255, 255, 255, 255)
	) :
		bounds(position, Size2(sizeX, sizeY)),
		vertex_color{ color, color, color, color }
	{}
	Rectangle(
		Type sizeX,
		Type sizeY,
		Type positionX = 0,
		Type positionY = 0,
		const Color& color = Color(255, 255, 255, 255)
	) :
		bounds(Point2(positionX, positionY), Size2(sizeX, sizeY)),
		vertex_color{ color, color, color, color }
	{}
	Rectangle(
		Type sizeX,
		Type sizeY,
		Type positionX = 0,
		Type positionY = 0,
		u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
	) :
		bounds(Point2(positionX, positionY), Size2(sizeX, sizeY)),
		vertex_color({ Color(r,g,b,a),Color(r,g,b,a),Color(r,g,b,a),Color(r,g,b,a) })
	{}
	~Rectangle() = default;
	void setPosition(const Point2<Type>& position) override final {
		bounds.position = position;
		this->setDirty();
	}
	void setPosition(Type positionX, Type positionY) override final {
		bounds.position = Point2<Type>(positionX, positionY);
		this->setDirty();
	}
	void setFillColor(const Color& color) override final {
		vertex_color = { color, color, color, color };
		this->setDirty();
	}
	void setFillColor(u8 r, u8 g, u8 b, u8 a = 255) override final {
		vertex_color = { Color(r, g, b, a),Color(r, g, b, a),Color(r, g, b, a),Color(r, g, b, a) };
		this->setDirty();
	}
	void setSize(const Size2<Type>& size) override final {
		bounds.size = size;
		this->setDirty();
	}
	void setSize(Type width, Type height) override final {
		bounds.size = Size2<Type>(width, height);
		this->setDirty();
	}
	boolean contains(const Point2<Type>& point) const override final {
		return bounds.contains(point);
	}
	boolean intersects(const Shape2D<Type>& other) const override final {
		const Rectangle<Type>* rectptr = dynamic_cast<const Rectangle<Type>*>(&other);
		if (rectptr) {
			return bounds.intersects(rectptr->bounds);
		}
		return false;
	}
	boolean isSolidColor() const override final {
		auto colorequaltofirst = [&](const Color& color) -> boolean {
			return color == vertex_color[std::to_underlying(RectangleVertex::top_left)];
			};
		return std::all_of(vertex_color.begin(), vertex_color.end(), colorequaltofirst);
	}
	[[nodiscard]] Point2<Type> getPosition() const override final {
		return bounds.position;
	}
	[[nodiscard]] Size2<Type> getSize() const override final {
		return bounds.size;
	}
	std::optional<Color> getFillColor() const override final {
		if (!isSolidColor()) return std::nullopt;
		else return vertex_color[std::to_underlying(RectangleVertex::top_left)];
	}
	template <typename CopyType>
	requires std::is_arithmetic_v<CopyType>
	Rectangle<std::common_type_t<CopyType, Type>> perfectCopy() const {
		Rectangle<CopyType> copyrectangle;
		copyrectangle.bounds = bounds;
		copyrectangle.vertex_color = vertex_color;
		copyrectangle.transform = transform;
		copyrectangle.setDrawId(this->getDrawIdValue());
		if (this->isClean()) {
			copyrectangle.setClean();
		}
		else {
			copyrectangle.setDirty();
		}
		return copyrectangle;
	}
	void setVertexColor(const RectangleVertex& rectanglevertex, const Color& color) {
		vertex_color[std::to_underlying(rectanglevertex)] = color;
	}
	void setVertexColor(const RectangleVertex& rectanglevertex, u8 r, u8 g, u8 b, u8 a = 255) {
		vertex_color[std::to_underlying(rectanglevertex)] = Color(r, g, b, a);
	}
	std::optional<RectBounds<Type>> getIntersection(const Rectangle<Type>& other) const {
		return bounds.getIntersection(other.bounds);
	}
	Color getVertexColor(const RectangleVertex& rectanglevertex) const {
		return vertex_color[std::to_underlying(rectanglevertex)];
	}
	std::array<Color, std::to_underlying(RectangleVertex::amount)> getVerticesColors() const {
		return vertex_color;
	}
	std::array<Point2<Type>, std::to_underlying(RectangleVertex::amount)> getVertexPositions() const {
		std::array<Point2<Type>, std::to_underlying(RectangleVertex::amount)> vertices = { bounds.topLeft(), bounds.topRight(), bounds.bottomLeft(), bounds.bottomRight() };
		return vertices;
	}
	std::array<Vertex, std::to_underlying(RectangleVertex::amount)> getFullVertexData() const {
		const Color& topleftcolor = vertex_color[std::to_underlying(RectangleVertex::top_left)];
		const Color& toprightcolor = vertex_color[std::to_underlying(RectangleVertex::top_right)];
		const Color& bottomleftcolor = vertex_color[std::to_underlying(RectangleVertex::bottom_left)];
		const Color& bottomrightcolor = vertex_color[std::to_underlying(RectangleVertex::bottom_right)];
		std::array<Vertex, std::to_underlying(RectangleVertex::amount)> fullvertexdata = {
			Vertex(
				MathUtils::normalize_position_2d(bounds.topLeft().x,Axis::x),
				MathUtils::normalize_position_2d(bounds.topLeft().y,Axis::y),
				0,
				MathUtils::normalize_color(topleftcolor.r),
				MathUtils::normalize_color(topleftcolor.g),
				MathUtils::normalize_color(topleftcolor.b),
				MathUtils::normalize_color(topleftcolor.a)
			),
			Vertex(
				MathUtils::normalize_position_2d(bounds.topRight().x,Axis::x),
				MathUtils::normalize_position_2d(bounds.topRight().y,Axis::y),
				0,
				MathUtils::normalize_color(toprightcolor.r),
				MathUtils::normalize_color(toprightcolor.g),
				MathUtils::normalize_color(toprightcolor.b),
				MathUtils::normalize_color(toprightcolor.a)
			),
			Vertex(
				MathUtils::normalize_position_2d(bounds.bottomLeft().x,Axis::x),
				MathUtils::normalize_position_2d(bounds.bottomLeft().y,Axis::y),
				0,
				MathUtils::normalize_color(bottomleftcolor.r),
				MathUtils::normalize_color(bottomleftcolor.g),
				MathUtils::normalize_color(bottomleftcolor.b),
				MathUtils::normalize_color(bottomleftcolor.a)
			),
			Vertex(
				MathUtils::normalize_position_2d(bounds.bottomRight().x,Axis::x),
				MathUtils::normalize_position_2d(bounds.bottomRight().y,Axis::y),
				0,
				MathUtils::normalize_color(bottomrightcolor.r),
				MathUtils::normalize_color(bottomrightcolor.g),
				MathUtils::normalize_color(bottomrightcolor.b),
				MathUtils::normalize_color(bottomrightcolor.a)
			),
		};
		return fullvertexdata;
	}
};
using FloatRectangle = Rectangle<f32>;
using IntRectangle = Rectangle<i32>;
using UIntRectangle = Rectangle<u32>;