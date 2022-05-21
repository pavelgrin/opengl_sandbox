#pragma once

class Texture2D
{
private:
    unsigned int m_id;

public:
    Texture2D(const int width, const int height, const bool alpha, const unsigned char* data);
    ~Texture2D();

    void bind();
};
