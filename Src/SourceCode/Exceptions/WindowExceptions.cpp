#include "Exceptions/WindowExceptions.hpp"
namespace oge {
	WindowException::WindowException(const std::string& msg) {
		message = msg;
	}
	const char* WindowException::what() const noexcept {
		return message.c_str();
	}
}