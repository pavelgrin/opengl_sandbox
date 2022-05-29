#pragma once

#include <string>

class Shader;

class Texture2D
{
private:
    unsigned int m_id;
    std::string m_name;

public:
    Texture2D(const int width, const int height, const bool alpha, const unsigned char* data);
    ~Texture2D();

    void bind(Shader* shader, std::string name, unsigned int index);
};
