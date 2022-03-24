#include "./render/render.hpp"
#include "./window/window.hpp"
#include <iostream>

int main() {
    Render render;
    Window window;

    window.create(800, 600, "OpenGL Sandbox", &render);

    return 0;
}
