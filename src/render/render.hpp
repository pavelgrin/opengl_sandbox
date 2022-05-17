#pragma once

#include "../mesh/mesh.hpp"
#include "../shader/shader.hpp"
#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
    void frame(uint64_t time_ms) const;
    void processInput(SDL_Event event) const;
};
