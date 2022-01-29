#include "./window/window.hpp"
#include "./render/render.hpp"

void runSDL2() {
    Window *window_sdl2 = new WindowSDL2();
    Render render(*window_sdl2);

    delete window_sdl2;
}

void runGLFW() {
    Window *window_glfw = new WindowGLFW();
    Render render(*window_glfw);

    delete window_glfw;
}

int main() {
    runSDL2();
    // runGLFW();
    return 0;
}
