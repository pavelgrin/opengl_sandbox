#include "./render.hpp"

void Render::frame() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render::processInput(SDL_Event event) const {
    //
}
