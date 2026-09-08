#include <Calculations/General/Color.hpp>
#include <Calculations/General/Types.hpp>
#include <algorithm>
Color::Color(u8 red, u8 green, u8 blue, u8 alpha) :
	r(std::clamp<u8>((red), 0, 255)),
	g(std::clamp<u8>(green, 0, 255)),
	b(std::clamp<u8>(blue, 0, 255)),
	a(std::clamp<u8>(alpha, 0, 255))
{}
Color::Color(u32 hexvalue) {
	r = hexvalue >> 24;
	g = (hexvalue >> 16) & 0xFF;
	b = (hexvalue >> 8) & 0xFF;
	a = hexvalue & 0xFF;
}
Color Color::operator+(const Color& other) const {
	return Color(
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) + other.r, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) + other.g, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) + other.b, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) + other.a, 0, 255))
	);
}
Color Color::operator-(const Color& other) const {
	return Color(
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) - other.r, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) - other.g, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) - other.b, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) - other.a, 0, 255))
	);
}
Color Color::operator*(const Color& other) const {
	return Color(
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) * other.r, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) * other.g, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) * other.b, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) * other.a, 0, 255))
	);
}
Color Color::operator/(const Color& other) const {
	return Color(
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) / other.r, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) / other.g, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) / other.b, 0, 255)),
		static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) / other.a, 0, 255))
	);
}
Color& Color::operator+=(const Color& other) {
	r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) + other.r, 0, 255));
	g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) + other.g, 0, 255));
	b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) + other.b, 0, 255));
	a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) + other.a, 0, 255));
	return *this;
}
Color& Color::operator-=(const Color& other) {
	r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) + other.r, 0, 255));
	g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) - other.g, 0, 255));
	b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) - other.b, 0, 255));
	a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) - other.a, 0, 255));
	return *this;
}
Color& Color::operator*=(const Color& other) {
	r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) * other.r, 0, 255));
	g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) * other.g, 0, 255));
	b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) * other.b, 0, 255));
	a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) * other.a, 0, 255));
	return *this;
}
Color& Color::operator/=(const Color& other) {
	r = static_cast<u8>(std::clamp<u16>(static_cast<u16>(r) / other.r, 0, 255));
	g = static_cast<u8>(std::clamp<u16>(static_cast<u16>(g) / other.g, 0, 255));
	b = static_cast<u8>(std::clamp<u16>(static_cast<u16>(b) / other.b, 0, 255));
	a = static_cast<u8>(std::clamp<u16>(static_cast<u16>(a) / other.a, 0, 255));
	return *this;
}