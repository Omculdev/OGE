#pragma once
#include "Utils/General/Logger.hpp"
#include "Calculations/General/Types.hpp"
#include "Utils/Enums/Keys.hpp"
#include "Rendering/Window.hpp"
#include <GLFW/glfw3.h>
#include <array>
#include <utility>
#include <functional>
#include <type_traits>
class Application;
class Keyboard {
private:
	std::array<boolean, std::to_underlying(Key::amount)> current_keys_pressed = {};
	std::array<boolean, std::to_underlying(Key::amount)> previous_keys_pressed = {};
	Window* current_window = {};
	i16 key_to_glfw(Key key) const;
	void init(Window* window);
	void bindWindow(Window* window);
	void update();
public:
	Keyboard() = default;
	Keyboard(const Keyboard& other) = delete;
	Keyboard& operator=(const Keyboard& other) = delete;
	Keyboard(Keyboard&& other) noexcept;
	Keyboard& operator=(Keyboard&& other) noexcept;
	boolean isHeld(Key key) const;
	boolean isPressed(Key key) const;
	boolean isReleased(Key key) const;
	boolean anyKeyPressed() const;
	boolean anyKeyHeld() const;
	boolean anyKeyReleased() const;
	template <typename Func, typename... Args>
	requires (!std::same_as<std::invoke_result_t<Func, Args...>, void>)
	std::optional<std::invoke_result_t<Func, Args...>> doOnKeyPress(Key key, Func&& function, Args&&... arguments) const {
		if (!isPressed(key)) {
			return std::nullopt;
		}
		return std::invoke(std::forward<Func>(function), std::forward<Args>(arguments)...);
	}
	template <typename Func, typename... Args>
	requires std::same_as<std::invoke_result_t<Func, Args...>, void>
	void doOnKeyPress(Key key, Func&& function, Args&&... arguments) const {
		if (!isPressed(key)) {
			return;
		}
		std::invoke(std::forward<Func>(function), std::forward<Args>(arguments)...);
	}
	template <typename Func, typename... Args>
	requires (!std::same_as<std::invoke_result_t<Func, Args...>, void>)
	std::optional<std::invoke_result_t<Func, Args...>> doOnKeyRelease(Key key, Func&& function, Args&&... arguments) const {
		if (!isReleased(key)) {
			return std::nullopt;
		}
		return std::invoke(std::forward<Func>(function), std::forward<Args>(arguments)...);
	}
	template <typename Func, typename... Args>
	requires std::same_as<std::invoke_result_t<Func, Args...>, void>
	void doOnKeyRelease(Key key, Func&& function, Args&&... arguments) const {
		if (!isReleased(key)) {
			return;
		}
		std::invoke(std::forward<Func>(function), std::forward<Args>(arguments)...);
	}
	template <typename Func, typename... Args>
	requires (!std::same_as<std::invoke_result_t<Func, Args...>, void>)
	std::optional<std::invoke_result_t<Func, Args...>> doOnKeyHold(Key key, Func&& function, Args&&... arguments) const {
		if (!isHeld(key)) {
			return std::nullopt;
		}
		return std::invoke(std::forward<Func>(function), std::forward<Args>(arguments)...);
	}
	template <typename Func, typename... Args>
	requires std::same_as<std::invoke_result_t<Func, Args...>, void>
	void doOnKeyHold(Key key, Func&& function, Args&&... arguments) const {
		if (!isHeld(key)) {
			return;
		}
		std::invoke(std::forward<Func>(function), std::forward<Args>(arguments)...);
	}
	friend class Application;
};