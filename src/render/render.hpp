#pragma once

#include "../shader/shader.hpp"
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <string>

class Render final
{
  private:
    std::string m_resource_dir;
    Shader m_shader;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

  public:
    Render(std::string resources_dir) : m_resource_dir(resources_dir) {}
    ~Render();

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
