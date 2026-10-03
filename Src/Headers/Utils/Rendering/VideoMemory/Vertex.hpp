#pragma once
#include "Calculations/General/Types.hpp"
#include <type_traits>
class Vertex {
public:
	f32 x = {};
	f32 y = {};
	f32 z = {};
	f32 r = {};
	f32 g = {};
	f32 b = {};
	f32 a = {};
	Vertex(f32 x, f32 y, f32 z, f32 r, f32 g, f32 b, f32 a = 1.0f) : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}
	Vertex(const Vertex& other) = default;
	Vertex& operator=(const Vertex& other) = default;
	Vertex(Vertex&& other) noexcept = default;
	Vertex& operator=(Vertex&& other) noexcept = default;
	~Vertex() = default;
};
