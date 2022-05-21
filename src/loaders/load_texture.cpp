#include "../render/texture.hpp"
#include "./loaders.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture2D* loadTexture(const char* file, const bool alpha)
{
    int width;
    int height;
    int nr_channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file, &width, &height, &nr_channels, 0);

    if (!data)
    {
        std::cerr << "ERROR::TEXTURE::File not succesfully read\n";
        return nullptr;
    }

    Texture2D* texture = new Texture2D(width, height, alpha, data);
    stbi_image_free(data);
    return texture;
}
