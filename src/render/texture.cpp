#include "./texture.hpp"
#include "./shader.hpp"
#include <glad/glad.h>

Texture2D::Texture2D(const int width, const int height, const int channels, const unsigned char* data)
{
    unsigned int image_format;
    if (channels == 1)
        image_format = GL_RED;
    else if (channels == 3)
        image_format = GL_RGB;
    else if (channels == 4)
        image_format = GL_RGBA;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, image_format, width, height, 0,
                 image_format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind(Shader* shader, std::string name, unsigned int index)
{
    if (m_name != name)
    {
        m_name = name;
        shader->setInt(name, index);
    }

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
