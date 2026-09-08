#pragma once
#include <exception>
#include <string>
namespace oge {
	class WindowException : public std::exception {
	private:
		std::string message = {};
	public:
		explicit WindowException(const std::string& msg);
		const char* what() const noexcept override;
	};
}