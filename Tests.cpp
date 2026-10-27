#include "Rendering/Application.hpp"
int main() {
    float positionX = 950;
    float positionY = 875;
    Application app;
    app.addWindow(1600, 1080, "darn");
    FloatRectangle HV1;
    HV1.setSize(50, 600);
    HV1.setPosition(400, 600);
    HV1.setFillColor(255, 0, 0);
    FloatRectangle HV2;
    HV2.setSize(50, 600);
    HV2.setPosition(700, 600);
    HV2.setFillColor(0, 255, 0);
    FloatRectangle HH1;
    HH1.setSize(250, 50);
    HH1.setPosition(550, 600);
    HH1.setFillColor(0, 0, 255);
    IntRectangle IV1;
    IV1.setSize(50, 500);
    IV1.setPosition(950, 550);
    IV1.setVertexColor(RectangleVertex::top_left, 255, 0, 255);
    IV1.setVertexColor(RectangleVertex::top_right, 255, 0, 0);
    IV1.setVertexColor(RectangleVertex::bottom_left, 0, 0, 255);
    IV1.setVertexColor(RectangleVertex::bottom_right, 255, 255, 0);
    IntRectangle IV2;
    IV2.setSize(50, 50);
    IV2.setPosition(950, 875);
    IV2.setVertexColor(RectangleVertex::top_left, 0, 255, 0);
    IV2.setVertexColor(RectangleVertex::bottom_left, 255, 255, 0);
    IV2.setVertexColor(RectangleVertex::bottom_right, 255, 0, 0);
    IV2.setVertexColor(RectangleVertex::top_right, 0, 0, 255);
    while (!app.currentWindowShouldClose()) {
        app.clearCurrentWindow(0,0,0);
        app.draw(HV1);
        app.draw(HV2);
        app.draw(HH1);
        app.draw(IV1);
        if (app.keyboard.isHeld(Key::W)) {
            positionY += 0.1f;
        }
        else if (app.keyboard.isHeld(Key::S)) {
            positionY -= 0.1f;
        }
        else if (app.keyboard.isHeld(Key::A)) {
            positionX -= 0.1f;
        }
        else if (app.keyboard.isHeld(Key::D)) {
            positionX += 0.1f;
        }
        IV2.setPosition(positionX, positionY);
        app.draw(IV2);
        app.displayCurrentWindow();
    }
    return 0;
}