#pragma once
#include <GLAD/glad.h>	
#include <GLFW/glfw3.h>
#include <string>
#include <Calculations/General/Color.hpp>
#include <Calculations/2D/Size2.hpp>
	class Window {
	private:
		GLFWwindow* window_pointer = {};
		bool depth_enabled = {};
		void initGLFW();
		void basic_create(const UIntSize2& size, const std::string& title, bool enable_depth);
		static inline void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}
	public:
		Window();
		~Window();
		Window(u32 width, u32 height, const std::string& title, bool enable_depth = false);
		Window(const UIntSize2& size, const std::string& title, bool enable_depth = false);
		void create(u32 width, u32 height, const std::string& title, bool enable_depth = false);
		void create(const UIntSize2& size, const std::string& title, bool enable_depth = false);
		bool shouldClose() const;
		void display() const;
		GLFWwindow* getPointer() const;
		bool depthEnabled() const;
	};