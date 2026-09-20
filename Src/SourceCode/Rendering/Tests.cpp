#include "Rendering/Application.hpp"
int main() {
    Application test;
    test.addWindow(1600, 1080, "darn");
    IntRectangle testrect;
    testrect.setPosition(300, 300);
    testrect.setVertexColor(RectangleVertex::top_left, 255, 0, 0);
    testrect.setVertexColor(RectangleVertex::top_right, 0, 255, 0);
    testrect.setVertexColor(RectangleVertex::bottom_right, 0, 0, 255);
    testrect.setVertexColor(RectangleVertex::bottom_left, 255, 255, 0);
    testrect.setSize(500, 500);
    IntRectangle testrect2;
    testrect2.setPosition(700, 500);
    testrect2.setVertexColor(RectangleVertex::top_left, 255, 0, 0);
    testrect2.setVertexColor(RectangleVertex::top_right, 0, 255, 0);
    testrect2.setVertexColor(RectangleVertex::bottom_right, 0, 0, 255);
    testrect2.setVertexColor(RectangleVertex::bottom_left, 255, 255, 0);
    testrect2.setSize(700, 700);
    while (!test.currentWindowShouldClose()) {
        test.clearCurrentWindow(0,0,0);
        test.draw(testrect);
        test.draw(testrect2);
        test.displayCurrentWindow();
    }
}