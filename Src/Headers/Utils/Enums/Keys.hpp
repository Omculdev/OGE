#pragma once
#include <GLFW/glfw3.h>
enum class Key {
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
	LeftShift, RightShift, LeftControl, RightControl, LeftAlt, RightAlt, LeftSuper, RightSuper,
	BackSlash, Comma, Equal, Minus, Slash, Semicolon, LeftBracket, RightBracket, GraveAccent, Apostrophe, Period, Pause, Menu, ScrollLock,
	Space, Backspace, Delete, Enter, End, Escape, Home, Insert, Menu, NumLock, PrintScreen, Tab,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
	Keypad0, KeyPad1, KeyPad2, KeyPad3, KeyPad4, KeyPad5, Keypad6, Keypad7, Keypad8, Keypad9,
	KeypadAdd, KeypadSubtract, KeypadMultiply, KeypadDivide, KeypadDecimal, KeypadEqual,
	UpArrow, DownArrow, LeftArrow, RightArrow,
	PageUp, PageDown, 
}; // exception to enum naming rule for the user's convenience