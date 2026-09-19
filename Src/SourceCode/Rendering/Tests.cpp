#include "Rendering/Renderer.hpp"
#include <iostream>
int main() {
    Logger::getInstance().init();
    Window test;
    test.create(1600, 1000, "lol");
    Renderer renderer;
    renderer.bindWindow(&test);
    FloatRectangle testtt;
    testtt.setFillColor(Color(255, 0, 0, 255));
    testtt.setPosition(500, 500);
    testtt.setSize(FloatSize2(200, 100));
    FloatRectangle testtt1;
    testtt1.setFillColor(Color(255, 255, 0, 255));
    testtt1.setPosition(300, 300);
    testtt1.setSize(FloatSize2(100, 100));
    std::cout << testtt1.getId();
    FloatRectangle testtt2;
    testtt2.setFillColor(Color(0, 255, 0, 255));
    testtt2.setPosition(800, 100);
    testtt2.setSize(FloatSize2(50, 100));
    std::cout << testtt2.getId();
    while (!test.shouldClose()) {
        renderer.clear(Color(255, 0, 0, 255));
        renderer.draw(testtt);
        renderer.draw(testtt1);
        renderer.draw(testtt2);
        test.display();
    }
}