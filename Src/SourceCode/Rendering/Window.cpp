#include "Rendering/Window.hpp"
#include <GLFW/glfw3.h>
#include <string>
#include "Utils/Logger.hpp"
#include "Exceptions/WindowExceptions.hpp"
namespace oge {
	void Window::initGLFW() {
		if (!glfwInit()) {
			Logger::getInstance().logFatal("Window::initGLFW: failed to init GLFW");
			throw oge::WindowException("Window::initGLFW: failed to init GLFW");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	void Window::basic_create(const UIntSize2& size, const std::string& title, bool enable_depth) {
		depth_enabled = enable_depth;
		Logger::getInstance().logInfo("Window::basic_create: attempting to create window with the following params: ");
		Logger::getInstance().logInfo("Window::basic_create: width: " + std::to_string(size.width));
		Logger::getInstance().logInfo("Window::basic_create: height: " + std::to_string(size.height));
		Logger::getInstance().logInfo("Window::basic_create: title: " + title);
		window = glfwCreateWindow(size.width, size.height, title.c_str(), NULL, NULL);
		if (!window) {
			Logger::getInstance().logFatal("Window::basic_create: failed to create window");
			throw oge::WindowException("Window::basic_create: failed to create window");
		}
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Logger::getInstance().logFatal("Window::basic_create: failed to initialize openGL functions");
			throw oge::WindowException("Window::basic_create: failed to initialize openGL functions");
		}
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	
		if (depth_enabled) {
			glEnable(GL_DEPTH_TEST);
		}

	}
	Window::Window() {
		initGLFW();
	}
	Window::~Window() {
		glfwTerminate();
	}
	Window::Window(u32 width, u32 height, const std::string& title, bool enable_depth) {
		initGLFW();
		basic_create(UIntSize2(width, height), title, enable_depth);
	}
	void Window::create(const UIntSize2& size, const std::string& title, bool enable_depth) {
		basic_create(size, title, enable_depth);
	}
	void Window::create(u32 width, u32 height, const std::string& title, bool enable_depth) {
		basic_create(UIntSize2(width, height), title, enable_depth);
	}
	bool Window::shouldClose() const {
		return glfwWindowShouldClose(window);
	}
	void Window::display() const {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}