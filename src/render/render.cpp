#include "./render.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Render::init()
{
    std::string vertex_path   = m_resources_dir + "shaders/shader.vs";
    std::string fragment_path = m_resources_dir + "shaders/shader.fs";

    std::vector<std::string> texture_paths{
        m_resources_dir + "textures/container.jpg",
        m_resources_dir + "textures/awesomeface.png",
    };

    std::vector<unsigned int> textures(texture_paths.size());

    // -------------------------------------------------------------------------
    int width, height, nrChannels;
    unsigned char* data;

    for (unsigned int i = 0; i < texture_paths.size(); ++i)
    {
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(texture_paths[i].c_str(), &width, &height, &nrChannels,
                         0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                         i % 2 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Failed to load texture\n";
        }
        stbi_image_free(data);
    }
    // -------------------------------------------------------------------------

    // clang-format off
    std::vector<float> vertices{
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    std::vector<unsigned int> indices{ 
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // clang-format on

    m_shader.init(vertex_path.c_str(), fragment_path.c_str());
    m_square.init(m_shader, vertices, indices, textures);
}

void Render::frame() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_square.draw();
}

void Render::processInput(SDL_Event event) const
{
    //
}
