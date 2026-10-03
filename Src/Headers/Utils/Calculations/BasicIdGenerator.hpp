#pragma once
#include "Calculations/General/Types.hpp"
#include <type_traits>
template <typename Type>
requires std::is_arithmetic_v<Type>
class BasicIdGenerator {
private:
	static inline Type current_id = {};
public:
	static inline [[nodiscard]] Type getId() {
		if (current_id == 0) {
			current_id++;
		}
		return current_id;
	}
	static inline [[nodiscard]] Type assignId() {
		current_id++;
		return current_id;
	}
	static inline void increment() {
		current_id++;
	}
};