#pragma once
#include "Shape2D.hpp"
#include "Utils/Enums/RectangleVertices.hpp"
#include "Utils/VideoMemory/Vertex.hpp"
#include <Calculations/2D/Point2.hpp>
#include <Calculations/2D/RectBounds.hpp>
#include <Calculations/2D/Size2.hpp>
#include <Calculations/General/Color.hpp>
#include <Calculations/General/Types.hpp>
#include "Rendering/Renderer.hpp"
#include <GLM/fwd.hpp>
#include <algorithm>
#include <array>
#include <optional>
#include <type_traits>
#include "Utils/VideoMemory/Mesh.hpp"
#include "Utils/General/IdGenerator.hpp"
#include "Utils/General/MathUtils.hpp"
template<typename Type>
requires std::is_arithmetic_v<Type>
class Rectangle : public Shape2D<Type> {
private:
	static inline IdGenerator id_generator = {};
	glm::mat4 transform = glm::mat4(1.0f);
	std::array<Color, static_cast<usize>(RectangleVertex::amount)> vertex_color;
	RectBounds<Type> bounds = {};
	u32 id = {};
public:
	Rectangle() : id(id_generator.assignId()) {}
	Rectangle(const Rectangle& other) :
		bounds(other.bounds),
		transform(other.transform),
		vertex_color(other.vertex_color),
		id(id_generator.assignId())
	{}
	Rectangle& operator=(const Rectangle& other) {
		if (this == &other) return *this;
		bounds = other.bounds;
		transform = other.transform;
		vertex_color = other.vertex_color;
		id = id_generator.assignId();
		return *this;
	}
	Rectangle(Rectangle&& other) noexcept  :
		bounds(std::move(other.bounds)),
		transform(std::move(other.transform)),
		vertex_color(std::move(other.vertex_color)),
		id(other.id)
	{
		other.id = 0;
	}
	Rectangle& operator=(Rectangle&& other) noexcept {
		if (this == &other) return *this;
		bounds = std::move(other.bounds);
		transform = std::move(other.transform);
		vertex_color = std::move(other.vertex_color);
		id = other.id;
		other.id = 0;
		return *this;
	}
	Rectangle(
		const Size2<Type>& size,
		const Point2<Type>& position = Point2<Type>(0, 0),
		const Color& color = Color(255, 255, 255, 255)
	) :
		bounds(position, size),
		vertex_color{ color, color, color, color }
	{
		id = id_generator.assignId();
	}
	Rectangle(
		Type sizeX, Type sizeY,
		const Point2<Type>& position = Point2<Type>(0, 0),
		const Color& color = Color(255, 255, 255, 255)
	) :
		bounds(position, Size2(sizeX, sizeY)),
		vertex_color{ color, color, color, color }
	{
		id = id_generator.assignId();
	}
	Rectangle(
		Type sizeX,
		Type sizeY,
		Type positionX = 0,
		Type positionY = 0,
		const Color& color = Color(255, 255, 255, 255)
	) :
		bounds(Point2(positionX, positionY), Size2(sizeX, sizeY)),
		vertex_color{ color, color, color, color }
	{
		id = id_generator.assignId();
	}
	Rectangle(
		Type sizeX,
		Type sizeY,
		Type positionX = 0,
		Type positionY = 0,
		u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
	) :
		bounds(Point2(positionX, positionY), Size2(sizeX, sizeY)),
		vertex_color({ Color(r,g,b,a),Color(r,g,b,a),Color(r,g,b,a),Color(r,g,b,a) })
	{
		id = id_generator.assignId();
	}
	~Rectangle() {
		id = 0;
	}
	void setPosition(const Point2<Type>& position) override final {
		bounds.position = position;
	}
	void setPosition(Type positionX, Type positionY) override final {
		bounds.position = Point2<Type>(positionX, positionY);
	}
	void setFillColor(const Color& color) override final {
		vertex_color = { color, color, color, color };
	}
	void setFillColor(u8 r, u8 g, u8 b, u8 a = 255) override final {
		vertex_color = { Color(r, g, b, a),Color(r, g, b, a),Color(r, g, b, a),Color(r, g, b, a) };
	}
	void setSize(const Size2<Type>& size) override final {
		bounds.size = size;
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
			return color == vertex_color[static_cast<usize>(RectangleVertex::top_left)];
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
		else return vertex_color[static_cast<usize>(RectangleVertex::top_left)];
	}
	void setVertexColor(const RectangleVertex& rectanglevertex, const Color& color) {
		vertex_color[static_cast<usize>(rectanglevertex)] = color;
	}
	std::optional<RectBounds<Type>> getIntersection(const Rectangle<Type>& other) const {
		return bounds.getIntersection(other);
	}
	Color getVertexColor(const RectangleVertex& rectanglevertex) const {
		return vertex_color[static_cast<usize>(rectanglevertex)];
	}
	std::array<Color, static_cast<usize>(RectangleVertex::amount)> getVerticesColors() const {
		return vertex_color;
	}
	std::array<Point2<Type>, static_cast<usize>(RectangleVertex::amount)> getVertexPositions() const {
		std::array<Point2<Type>, static_cast<usize>(RectangleVertex::amount)> vertices = { bounds.topLeft(), bounds.topRight(), bounds.bottomLeft(), bounds.bottomRight() };
		return vertices;
	}
	std::array<Vertex<Type>, static_cast<usize>(RectangleVertex::amount)> getFullVertexData() const {
		const Color& topleftcolor = vertex_color[static_cast<usize>(RectangleVertex::top_left)];
		const Color& toprightcolor = vertex_color[static_cast<usize>(RectangleVertex::top_right)];
		const Color& bottomleftcolor = vertex_color[static_cast<usize>(RectangleVertex::bottom_left)];
		const Color& bottomrightcolor = vertex_color[static_cast<usize>(RectangleVertex::bottom_right)];
		std::array<Vertex<Type>, static_cast<usize>(RectangleVertex::amount)> fullvertexdata = {
			Vertex<Type>(
				MathUtils::normalize_position_2d(bounds.topLeft().x,Axis::x),
				MathUtils::normalize_position_2d(bounds.topLeft().y,Axis::y),
				0,
				MathUtils::normalize_color(topleftcolor.r),
				MathUtils::normalize_color(topleftcolor.g),
				MathUtils::normalize_color(topleftcolor.b),
				MathUtils::normalize_color(topleftcolor.a)
			),
			Vertex<Type>(
				MathUtils::normalize_position_2d(bounds.topRight().x,Axis::x),
				MathUtils::normalize_position_2d(bounds.topRight().y,Axis::y),
				0,
				MathUtils::normalize_color(toprightcolor.r),
				MathUtils::normalize_color(toprightcolor.g),
				MathUtils::normalize_color(toprightcolor.b),
				MathUtils::normalize_color(toprightcolor.a)
			),
			Vertex<Type>(
				MathUtils::normalize_position_2d(bounds.bottomLeft().x,Axis::x),
				MathUtils::normalize_position_2d(bounds.bottomLeft().y,Axis::y),
				0,
				MathUtils::normalize_color(bottomleftcolor.r),
				MathUtils::normalize_color(bottomleftcolor.g),
				MathUtils::normalize_color(bottomleftcolor.b),
				MathUtils::normalize_color(bottomleftcolor.a)
			),
			Vertex<Type>(
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
	u32 getId() const {
		return id;
	}
};
using FloatRectangle = Rectangle<f32>;
using IntRectangle = Rectangle<i32>;
using UIntRectangle = Rectangle<u32>;