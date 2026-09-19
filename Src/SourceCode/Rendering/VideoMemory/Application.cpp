#include "Rendering/Application.hpp"
Application::Application() {
	Logger::getInstance().init();
	current_window_index = 0;
}
Application::~Application() {
	glfwTerminate();
}
void Application::addWindow(u32 width, u32 height, const std::string& title, boolean enable_depth) {
	windows.emplace_back(width, height, title, enable_depth);
}
void Application::addWindow(const UIntSize2& size, const std::string& title, boolean enable_depth) {
	windows.emplace_back(size, title, enable_depth);
}
void Application::clearWindow(const Color& color) const {
	renderer.clear(color);
}
void Application::displayWindow() const {
	windows[current_window_index].display();
}
void Application::switchToWindow(usize index) {
	windows[current_window_index].makeContextCurrent();
}
[[nodiscard]] boolean Application::windowShouldClose() const {
	return windows[current_window_index].shouldClose();
}