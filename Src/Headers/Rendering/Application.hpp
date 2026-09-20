#pragma once
#include "Rendering/Window.hpp"
#include "Rendering/Renderer.hpp"
#include <type_traits>
class Application {
private:
	std::vector<Window> windows = {};
	Renderer renderer = {};
	usize current_window_index = {};
	boolean first_window_added = {};
	[[nodiscard]] boolean initGLFW();
public:
	Application(); // add more constructors with window params and shader types and dynamic/static draw
	~Application();
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	Application(Application&& other) = delete;
	Application operator=(Application& other) = delete;
	boolean addWindow(u32 width, u32 height, const std::string& title, boolean enable_depth = false);
	boolean addWindow(const UIntSize2& size, const std::string& title, boolean enable_depth = false);
	template <typename RectType> 
	requires std::is_arithmetic_v<RectType>
	void draw(const Rectangle<RectType>& rectangle) {
		renderer.draw(rectangle);
	}
	void switchToWindow(usize index);
	void clearCurrentWindow(const Color& color = Color(0,0,0,255)) const;
	void clearCurrentWindow(u8 r, u8 g, u8 b, u8 a = 255) const;
	void displayCurrentWindow();
	[[nodiscard]] boolean currentWindowShouldClose() const;
};