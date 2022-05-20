#pragma once

#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
    unsigned int m_id;

    ~Shader();

    void init(const char* vertex_path, const char* fragment_path);
    void use() const;
    void setInt(const std::string& name, int value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
};
