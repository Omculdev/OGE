#pragma once
#include "Calculations/General/Types.hpp"
class IdGenerator {
private:
	u32 current_id = {};
public:
	[[nodiscard]] u32 getId();
	[[nodiscard]] u32 assignId();
	void increment();
	IdGenerator& operator++();
};