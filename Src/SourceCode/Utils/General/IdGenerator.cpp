#include "Utils/General/IdGenerator.hpp"
u32 IdGenerator::getId() {
	if (current_id == 0) {
		current_id++;
	}
	return current_id;
}
u32 IdGenerator::assignId() {
	current_id++;
	return current_id;
}
void IdGenerator::increment() {
	current_id++;
}
IdGenerator& IdGenerator::operator++() {
	current_id++;
	return *this;
}