#pragma once

#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

class Render final
{
  private:
    int m_shader_program;
    unsigned int m_VAO;
    unsigned int m_VBO;

  public:
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
