#pragma once
#include "Calculations/General/Types.hpp"
struct AttributePointer {
public:
	u32 layout = {};
	u32 type = {};
	usize size = {};
	usize stride = {};
	usize shift = {};
	boolean normalized = {};
};