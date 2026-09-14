#include "Exceptions/WindowExceptions.hpp"
#include <string>
WindowException::WindowException(const std::string& msg) {
	message = msg;
}
const char* WindowException::what() const noexcept {
	return message.c_str();
}