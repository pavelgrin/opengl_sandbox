#pragma once

#include "./shader.hpp"
#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    ~Mesh();

    void init(Shader shader,
              std::vector<float> vertices,
              std::vector<unsigned int> indices,
              std::vector<unsigned int> textures);
    void draw() const;

private:
    Shader m_shader;
    std::vector<unsigned int> m_textures;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};
