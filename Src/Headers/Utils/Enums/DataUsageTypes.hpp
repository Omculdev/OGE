#pragma once
#include <GLAD/glad.h>
enum class DataUsageType {
	static_draw, dynamic_draw, stream_draw, 
	static_copy, dynamic_copy, stream_copy,
	static_read, dynamic_read, stream_read,
	amount, none
};