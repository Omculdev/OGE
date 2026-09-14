#include "Rendering/Window.hpp"
#include "Rendering/Renderer.hpp"
#include <iostream>
int main() {
	Window test;
	test.create(1600, 1000, "lol");
	Renderer renderer;
	renderer.bindWindow(&test);
	while (!test.shouldClose()) {
		renderer.clear(Color(255, 0, 0, 255));
		test.display();
	}
}