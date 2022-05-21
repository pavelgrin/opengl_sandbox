#pragma once

#include "./shader.hpp"
#include "./texture.hpp"
#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    ~Mesh();

    void init(Shader* shader,
              std::vector<float> vertices,
              std::vector<unsigned int> indices,
              std::vector<Texture2D*> textures);
    void draw();

private:
    Shader* m_shader;
    std::vector<Texture2D*> m_textures;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};
