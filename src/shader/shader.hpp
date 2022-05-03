#pragma once

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
    unsigned int m_program_id;

  public:
    ~Shader();

    void init(const char* vertex_path, const char* fragment_path);
    void use() const;
};
