#pragma once
#include "Calculations/General/Types.hpp"
#include <optional>
template <typename HandleType>
class BasicHandle {
private:
	std::optional<HandleType> id = {};
public:
	BasicHandle() = default;
	BasicHandle(HandleType id) :
		id(id)
	{}
	BasicHandle(const BasicHandle& other) = delete;
	BasicHandle& operator=(const BasicHandle& other) = delete;
	BasicHandle(BasicHandle&& other) noexcept :
		id(other.id)
	{
		other.id = std::nullopt;
	}
	BasicHandle& operator=(BasicHandle&& other) noexcept {
		if (&other == this) return *this;
		id = other.id;
		other.id = std::nullopt;
		return *this;
	}
	boolean isValid() const {
		return id.has_value();
	}
	[[nodiscard]] std::optional<HandleType> getId() const {
		return id;
	}
	[[nodiscard]] HandleType getIdValue() const {
		return *id;
	}
	void setId(HandleType otherid) {
		id = otherid;
	}
	void invalidate() {
		id = std::nullopt;
	}
	auto operator<=>(const BasicHandle& other) const = default;
};