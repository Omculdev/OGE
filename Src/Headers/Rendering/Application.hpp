#pragma once
#include "Rendering/Window.hpp"
#include "Rendering/Renderer.hpp"
#include <type_traits>
class Application {
private:
	usize current_window_index = {};
	std::vector<Window> windows = {};
	Renderer renderer = {};
public:
	Application(); // add more constructors with window params and shader types and dynamic/static draw
	~Application();
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	Application(Application&& other) = delete;
	Application operator=(Application& other) = delete;
	void addWindow(u32 width, u32 height, const std::string& title, boolean enable_depth = false);
	void addWindow(const UIntSize2& size, const std::string& title, boolean enable_depth = false);
	template <typename RectType> 
	requires std::is_arithmetic_v<RectType>
	void draw(Rectangle<RectType> rectangle) {
		renderer.draw(rectangle);
	}
	void switchToWindow(usize index);
	void clearWindow(const Color& color = Color(0,0,0,255)) const;
	void displayWindow() const;
	[[nodiscard]] boolean windowShouldClose() const;
};