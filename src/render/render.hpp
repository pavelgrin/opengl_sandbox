#pragma once

#include "../camera/camera.hpp"
#include "../mesh/mesh.hpp"
#include "../shader/shader.hpp"
#include <SDL.h>
#include <cmath>
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
    Camera m_camera{glm::vec3(0.0f, 0.0f, 3.0f)};

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
    void frame(float dt_ms, float lifetime) const;
    void processInput(const uint8_t* keystates, const float dt, bool* is_window_open);
};
