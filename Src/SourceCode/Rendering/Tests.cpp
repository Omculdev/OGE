#include "Rendering/Application.hpp"
#include <iostream>
int main() {
    Application test;
    test.addWindow(1600, 1080, "darn");
    IntRectangle testrect;
    testrect.setPosition(700, 500);
    testrect.setFillColor(255, 0, 255);
    testrect.setVertexColor(RectangleVertex::top_right, Color(0, 255, 0));
    testrect.setSize(500, 100);
    while (!test.currentWindowShouldClose()) {
        test.clearCurrentWindow(0,0,0);
        test.draw(testrect);
        test.displayCurrentWindow();
    }
}