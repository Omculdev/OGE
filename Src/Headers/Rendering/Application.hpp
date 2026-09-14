#pragma once
#include "Rendering/Window.hpp"
#include "Rendering/Renderer.hpp"
#include <deque>
class Application {
private:
	std::deque<Window> current_window = {};
	Renderer renderer = {};
public:
	void addWindow(u32 width, u32 height, const std::string& title, bool enable_depth = false);
	void addWindow(const UIntSize2& size, const std::string& title, bool enable_depth = false);
	
};