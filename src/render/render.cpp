#include "./render.hpp"
#include "../loaders/loaders.hpp"
#include "../window/states.hpp"
#include "./camera.hpp"
#include "./mesh.hpp"
#include "./model.hpp"
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
Shader* Render::m_main_shader;
Shader* Render::m_light_shader;
Model* Render::m_object;

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

    // -------------------------------------------------------------------------
    std::string main_vertex_path    = res_dir + "shaders/main.vertex.glsl";
    std::string main_fragment_path  = res_dir + "shaders/main.fragment.glsl";
    std::string light_vertex_path   = res_dir + "shaders/light.vertex.glsl";
    std::string light_fragment_path = res_dir + "shaders/light.fragment.glsl";

    m_main_shader  = loadShader(main_vertex_path, main_fragment_path);
    m_light_shader = loadShader(light_vertex_path, light_fragment_path);

    std::string obj_resources_dir = res_dir + "objects/ponycar/";
    std::string obj_file          = obj_resources_dir + "Pony_cartoon.obj";

    m_object = loadModel(obj_file, obj_resources_dir);

    return 0;
}

void Render::update(EventStates* states,
                    EventActions* actions,
                    const float dt)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    processEvents(states, actions, dt);

    glm::mat4 projection = glm::perspective(glm::radians(m_camera.zoom()), m_aspect_ratio, 0.1f, 100.0f);
    glm::mat4 view       = m_camera.lookAt();

    glm::vec3 light_pos(2.0f, 2.0f, 2.0f);

    // Draw backpack
    m_main_shader->use();
    m_main_shader->setMat4("projection", projection);
    m_main_shader->setMat4("view", view);

    m_main_shader->setFloat("material.shininess", 32.0f);

    // m_main_shader->setVec3("light.position", light_pos);
    m_main_shader->setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

    m_main_shader->setVec3("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
    m_main_shader->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_main_shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    m_main_shader->setFloat("light.constant", 1.0f);
    m_main_shader->setFloat("light.linear", 0.09f);
    m_main_shader->setFloat("light.quadratic", 0.032f);

    m_main_shader->setVec3("view_pos", m_camera.getCameraPos());

    glm::mat4 model = glm::mat4(1.0f);
    model           = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model           = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    m_main_shader->setMat4("model", model);

    m_object->draw(m_main_shader);

    // // Draw light
    // glm::mat4 light_model = glm::mat4(1.0f);
    // light_model           = glm::translate(light_model, light_pos);
    // light_model           = glm::scale(light_model, glm::vec3(0.2f));

    // m_light_shader->use();
    // m_light_shader->setMat4("projection", projection);
    // m_light_shader->setMat4("view", view);
    // m_light_shader->setMat4("model", light_model);

    // // m_light->draw(m_light_shader);
    // // End draw light
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

void Render::fini()
{
    delete m_main_shader;
    delete m_light_shader;
    delete m_object;
}
