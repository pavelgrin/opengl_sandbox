#include "./render.hpp"
#include <glad/glad.h>
#include <iostream>

float Render::m_aspect_ratio = 1.0f;

int Render::init(const GLADloadproc get_proc_address,
                 const std::string res_dir,
                 const int viewport_width, const int viewport_height)
{
    if (!gladLoadGLLoader(get_proc_address))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    updateViewport(viewport_width, viewport_height);

    glEnable(GL_DEPTH_TEST);

    return 0;
}

void Render::update(EventStates* states,
                    EventActions* actions,
                    const float dt)
{
    processEvents(states, actions, dt);
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
}

void Render::updateViewport(const int width, const int height)
{
    m_aspect_ratio = static_cast<float>(width) / height;
    glViewport(0, 0, width, height);
}

void Render::fini() {}
