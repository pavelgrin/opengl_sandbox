#include "./render.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Render::init()
{
    glEnable(GL_DEPTH_TEST);

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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    std::vector<unsigned int> indices{ 
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // clang-format on

    m_shader.init(vertex_path.c_str(), fragment_path.c_str());
    m_square.init(m_shader, vertices, indices, textures);
}

void Render::frame(float dt, float lifetime) const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // const float radius = 10.0f;
    // float cam_x        = std::sin(lifetime) * radius;
    // float cam_z        = std::cos(lifetime) * radius;

    // glm::mat4 view = glm::lookAt(glm::vec3(cam_x, 0.0f, cam_z),
    //                              glm::vec3(0.0f, 0.0f, 0.0f),
    //                              glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view       = m_camera.lookAt();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.zoom()), 1.0f, 0.1f, 100.0f);

    m_shader.use();
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);

    glm::vec3 cube_positions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f),
    };

    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, cube_positions[i]);

        float base_angle = 20.0f * i + 20.0f;

        model = glm::rotate(model,
                            lifetime * glm::radians(base_angle),
                            glm::vec3(1.0f, 0.3f, 0.5f));

        m_shader.setMat4("model", model);
        m_square.draw();
    }
}

void Render::processInput(const uint8_t* keystates,
                          const int mouse_x_delta,
                          const int mouse_y_delta,
                          const int mouse_wheel_delta,
                          const float dt)
{
    float forward{0.0f};
    float backward{0.0f};
    float left{0.0f};
    float right{0.0f};
    float yaw{0.0f};
    float pitch{0.0f};
    float zoom{0.0f};

    const float velocity          = dt * 2.5f;
    const float mouse_sensitivity = 0.1f;

    yaw   = mouse_x_delta * mouse_sensitivity;
    pitch = mouse_y_delta * mouse_sensitivity * -1;
    zoom  = mouse_wheel_delta;

    if (keystates[SDL_SCANCODE_W])
        forward = velocity;
    if (keystates[SDL_SCANCODE_S])
        backward = velocity;
    if (keystates[SDL_SCANCODE_A])
        left = velocity;
    if (keystates[SDL_SCANCODE_D])
        right = velocity;

    m_camera.move({
        forward,
        backward,
        left,
        right,
        yaw,
        pitch,
        zoom,
    });
}
