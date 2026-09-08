#include "Rendering/Window.hpp"
#include <iostream>
int main() {
	oge::Window test;
	test.create(1600, 1000, "lol");
	while (!test.shouldClose()) {
		test.display();
	}
}