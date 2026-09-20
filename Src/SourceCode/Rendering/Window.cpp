#include "Rendering/Window.hpp"
#include "Utils/General/Logger.hpp"
#include <Calculations/2D/Size2.hpp>
#include <Calculations/General/Types.hpp>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
Window::Window(Window&& other) noexcept :
	depth_enabled(other.depth_enabled),
	window_pointer(other.window_pointer)
{
	other.window_pointer = nullptr;
}
Window& Window::operator=(Window&& other) noexcept {
	depth_enabled = other.depth_enabled;
	window_pointer = other.window_pointer;
	other.window_pointer = nullptr;
	return *this;
}
Window::~Window() {
	glfwDestroyWindow(window_pointer);
}
void Window::create(const UIntSize2& size, const std::string& title, boolean enabledepth) {
	depth_enabled = enabledepth;
	window_pointer = glfwCreateWindow(size.width, size.height, title.c_str(), NULL, NULL);
	if (!window_pointer) {
		Logger::getInstance().logWarning("Window::basic_create: failed to create window");
	}
	glfwSetWindowUserPointer(window_pointer, this);
	glfwSetFramebufferSizeCallback(window_pointer, framebuffer_size_callback);;
}
void Window::create(u32 width, u32 height, const std::string& title, boolean enabledepth) {
	create(UIntSize2(width, height), title, enabledepth);
}
Window::Window(const UIntSize2& size, const std::string& title, boolean enabledepth) {
	create(size, title, enabledepth);
}
Window::Window(u32 width, u32 height, const std::string& title, boolean enabledepth) {
	create(width, height, title, enabledepth);
}
boolean Window::shouldClose() const {
	return glfwWindowShouldClose(window_pointer);
}
void Window::display() const {
	glfwSwapBuffers(window_pointer);
	glfwPollEvents();
}
GLFWwindow* Window::getPointer() const {
	return window_pointer;
}
boolean Window::depthEnabled() const {
	return depth_enabled;
}
void Window::makeContextCurrent() const {
	glfwMakeContextCurrent(window_pointer);
}