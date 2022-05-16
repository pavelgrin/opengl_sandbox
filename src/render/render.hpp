#pragma once

#include "../mesh/mesh.hpp"
#include "../shader/shader.hpp"
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

class Render final
{
private:
    std::string m_resources_dir;

    Shader m_shader;
    Mesh m_square;

public:
    Render(std::string m_resources_dir) : m_resources_dir(m_resources_dir) {}

    void loadGLLoader(GLADloadproc getProcAddress) const
    {
        if (!gladLoadGLLoader(getProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
        }
    }

    void updateViewport(const int width, const int height) const
    {
        glViewport(0, 0, width, height);
    }

    void init();
    void frame() const;
    void processInput(SDL_Event event) const;
};
