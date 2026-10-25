#pragma once
#include "Calculations/2D/RectBounds.hpp"
#include "Calculations/2D/Point2.hpp"
#include "Calculations/General/Color.hpp"
#include <GLM/glm.hpp>
#include <optional>
template <typename Type>
class Shape2D {
protected:
	std::optional<u32> draw_id = {};
	boolean clean = {};
public:
	Shape2D() = default;
	explicit Shape2D(std::optional<u32> id) : draw_id(id) {}
	Shape2D(std::optional<u32> id, boolean clean) : draw_id(id), clean(clean) {}
	Shape2D(const Shape2D& other) : draw_id(std::nullopt), clean(false) {}
	Shape2D& operator=(const Shape2D& other) {
		if (&other == this) return *this;
		draw_id = std::nullopt;
		clean = false;
		return *this;
	}
	Shape2D(Shape2D&& other) noexcept :
		draw_id(other.draw_id),
		clean(other.clean)
	{
		other.draw_id = std::nullopt;
		other.clean = false;
	}
	Shape2D& operator=(Shape2D&& other) noexcept {
		if (this == &other) return *this;
		draw_id = other.draw_id;
		other.draw_id = std::nullopt;
		other.clean = false;
		return *this;
	}
	virtual ~Shape2D() = default;
	virtual void setPosition(const Point2<Type>& position) = 0;
	virtual void setPosition(Type positionX, Type positionY) = 0;
	virtual void setFillColor(const Color& color) = 0;
	virtual void setFillColor(u8 r, u8 g, u8 b, u8 a = 255) = 0;
	virtual void setSize(const Size2<Type>& size) = 0;
	virtual void setSize(Type width, Type height) = 0;
	virtual boolean contains(const Point2<Type>& point) const = 0;
	virtual boolean intersects(const Shape2D<Type>& shape) const = 0;
	virtual boolean isSolidColor() const = 0;
	virtual Point2<Type> getPosition() const = 0;
	virtual Size2<Type> getSize() const = 0;
	virtual std::optional<Color> getFillColor() const = 0;
	void resetDrawId() {
		draw_id = std::nullopt;
	}
	void setDrawId(u32 id) {
		draw_id = id;
	};
	[[nodiscard]] u32 getDrawIdValue() const {
		return *draw_id;
	}
	[[nodiscard]] std::optional<u32> getDrawId() const {
		return draw_id;
	}
	[[nodiscard]] boolean isClean() const {
		return clean;
	}
	void setClean() {
		clean = true;
	}
	void setDirty() {
		clean = false;
	}
};