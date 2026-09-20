#pragma once
#include <GLAD/glad.h>	
#include <GLFW/glfw3.h>
#include <string>
#include <Calculations/General/Color.hpp>
#include <Calculations/2D/Size2.hpp>
class Window {
private:
	GLFWwindow* window_pointer = {};
	boolean depth_enabled = {};
	static inline void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
public:
	Window() = default;
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	Window(Window&& other) noexcept;
	Window& operator=(Window&& other) noexcept;
	~Window();
	Window(u32 width, u32 height, const std::string& title, boolean enabledepth = false);
	Window(const UIntSize2& size, const std::string& title, boolean enabledepth = false);
	void create(u32 width, u32 height, const std::string& title, boolean enabledepth = false);
	void create(const UIntSize2& size, const std::string& title, boolean enabledepth = false);
	bool shouldClose() const;
	void display() const;
	GLFWwindow* getPointer() const;
	bool depthEnabled() const;
	void makeContextCurrent() const;
};