#include "Rendering/Application.hpp"
[[nodiscard]] boolean Application::initGLFW() {
	if (!glfwInit()) {
		Logger::getInstance().logWarning("Application:initGLFW: failed to init GLFW");
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}
Application::Application() {
	Logger::getInstance().init();
	current_window_index = 0;
}
Application::~Application() {
	glfwTerminate();
}
boolean Application::addWindow(const UIntSize2& size, const std::string& title, boolean enable_depth) {
	if (first_window_added) {
		windows.emplace_back(size, title, enable_depth);
	}
	if (!first_window_added) {
		if (!initGLFW()) {
			Logger::getInstance().logWarning("Application::addWindow: failed to initialize GLFW functions");
			return false;
		}
		windows.emplace_back(size, title, enable_depth);
		glfwMakeContextCurrent(windows[current_window_index].getPointer());
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Logger::getInstance().logWarning("Application::addWindow: failed to initialize openGL functions");
			return false;
		}
		renderer.init(&windows[current_window_index]);
		first_window_added = true;
	}
	glViewport(0, 0, size.width, size.height);
	return true;
}
boolean Application::addWindow(u32 width, u32 height, const std::string& title, boolean enable_depth) {
	return addWindow(UIntSize2(width, height), title, enable_depth);
}
void Application::clearCurrentWindow(const Color& color) const {
	renderer.clear(color);
}
void Application::clearCurrentWindow(u8 r, u8 g, u8 b, u8 a) const {
	clearCurrentWindow(Color(r, g, b, a));
}
void Application::displayCurrentWindow() {
	renderer.update();
	windows[current_window_index].display();
}
void Application::switchToWindow(usize index) {
	windows[current_window_index].makeContextCurrent();
}
[[nodiscard]] boolean Application::currentWindowShouldClose() const {
	return windows[current_window_index].shouldClose();
}