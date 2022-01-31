#include <iostream>
#include "./render/render.hpp"
#include "./window/window.hpp"

int main() {
    Render render;

    Window *window = new WindowSDL2();
    // Window *window = new WindowGLFW();

    window->create(800, 600, "OpenGL Sandbox", &render);

    delete window;
    return 0;
}
