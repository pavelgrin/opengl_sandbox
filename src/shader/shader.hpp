#pragma once

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
    unsigned int m_program_id;

    ~Shader();

    void init(const char* vertex_path, const char* fragment_path);
    void use() const;
    void setInt(const std::string& name, int value) const;
};
