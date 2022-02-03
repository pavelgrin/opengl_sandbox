#pragma once

#include <iostream>
#include <glad/glad.h>

class Render {
public:
    void loadGLLoader(GLADloadproc getProcAddress) const {
        gladLoadGLLoader(getProcAddress);
    }

    void updateViewport(const int width, const int height) const {
        glViewport(0, 0, width, height);
    }

    void frame() const;
    void processInput(int event) const;
};
