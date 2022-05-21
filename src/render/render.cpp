#include "./render.hpp"
#include "../loaders/loaders.hpp"
#include "./camera.hpp"
#include "./mesh.hpp"
#include "./shader.hpp"
#include "./texture.hpp"
#include <glad/glad.h>
#include <iostream>
#include <vector>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float Render::m_aspect_ratio = 1.0f;
Camera Render::m_camera;
Shader* Render::m_shader;
Mesh Render::m_square;

int Render::init(const GLADloadproc get_proc_address,
                 const std::string res_dir,
                 const int viewport_width, const int viewport_height)
{
    if (!gladLoadGLLoader(get_proc_address))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    updateViewport(viewport_width, viewport_height);

    std::string vertex_path   = res_dir + "shaders/main.vertex.glsl";
    std::string fragment_path = res_dir + "shaders/main.fragment.glsl";

    std::vector<std::string> texture_paths{
        res_dir + "textures/container.jpg",
        res_dir + "textures/awesomeface.png",
    };

    std::vector<Texture2D*> textures(texture_paths.size());

    textures[0] = loadTexture(texture_paths[0].c_str(), false);
    textures[1] = loadTexture(texture_paths[1].c_str(), true);

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

    m_shader = loadShader(vertex_path.c_str(), fragment_path.c_str());
    m_square.init(m_shader, vertices, indices, textures);

    return 0;
}

void Render::update(EventStates* states,
                    EventActions* actions,
                    const float dt)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    processEvents(states, actions, dt);

    glm::mat4 view       = m_camera.lookAt();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.zoom()), m_aspect_ratio, 0.1f, 100.0f);

    m_shader->use();
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);

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

    static float angle_changing = 1.0f;

    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, cube_positions[i]);

        float base_angle = 20.0f * i + 20.0f;

        model = glm::rotate(model,
                            angle_changing * glm::radians(base_angle),
                            glm::vec3(1.0f, 0.3f, 0.5f));

        m_shader->setMat4("model", model);
        m_square.draw();
    }

    angle_changing += 1.0f * dt;
}

void Render::processEvents(EventStates* states,
                           EventActions* actions,
                           const float dt)
{
    if (states->window_size.changed)
    {
        updateViewport(states->window_size.width,
                       states->window_size.height);
    }

    if (states->keystates[KeyCode::Escape])
    {
        actions->closeWindow(states);
    }

    actions->toggleCursor(states, states->mousestates[MouseCode::Right]);

    if (states->cursor_locked)
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

        yaw   = states->mouse_x_delta * mouse_sensitivity;
        pitch = states->mouse_y_delta * mouse_sensitivity * -1;
        zoom  = states->mouse_wheel_delta;

        if (states->keystates[KeyCode::W])
            forward = velocity;
        if (states->keystates[KeyCode::S])
            backward = velocity;
        if (states->keystates[KeyCode::A])
            left = velocity;
        if (states->keystates[KeyCode::D])
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
}

void Render::updateViewport(const int width, const int height)
{
    m_aspect_ratio = static_cast<float>(width) / height;
    glViewport(0, 0, width, height);
}

void Render::fini() {}
