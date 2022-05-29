#include "../render/texture.hpp"
#include "./loaders.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture2D* loadTexture(const std::string file)
{
    int width;
    int height;
    int nr_channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &nr_channels, 0);

    if (!data)
    {
        std::cerr << "ERROR::TEXTURE::File not succesfully read\n";
        return nullptr;
    }

    Texture2D* texture = new Texture2D(width, height, nr_channels, data);
    stbi_image_free(data);
    return texture;
}
