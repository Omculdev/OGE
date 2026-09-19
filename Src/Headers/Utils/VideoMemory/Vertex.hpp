#pragma once
#include "Calculations/General/Types.hpp"
#include <type_traits>
template <typename Type>
requires std::is_arithmetic_v<Type>
class Vertex {
public:
	Type x = {};
	Type y = {};
	Type z = {};
	Type r = {};
	Type g = {};
	Type b = {};
	Type a = {};
	Vertex(Type x, Type y, Type z, Type r, Type g, Type b, Type a = 255) : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}
	Vertex(const Vertex& other) = default;
	Vertex& operator=(const Vertex& other) = default;
	Vertex(Vertex&& other) noexcept = default;
	Vertex& operator=(Vertex&& other) noexcept = default;
	~Vertex() = default;
};
using FloatVertex = Vertex<f32>;
using IntVertex = Vertex<i32>;
using UIntVertex = Vertex<u32>;
