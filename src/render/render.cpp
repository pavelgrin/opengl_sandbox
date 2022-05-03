#include "./render.hpp"

void Render::init()
{
    std::string vertex_path   = m_resource_dir + "shaders/shader.vs";
    std::string fragment_path = m_resource_dir + "shaders/shader.fs";

    m_shader.init(vertex_path.c_str(), fragment_path.c_str());

    // std::cout << << std::endl;

    // // clang-format off
    // float vertices[] = {
    //    -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f,  0.5f, 0.0f,
    // };
    // // clang-format on

    // clang-format off
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left 
    };
    
    unsigned int indices[] = { 
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    // clang-format on

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(indices),
                 indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          3 * sizeof(float),
                          (void*)0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Render::frame() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader.use();
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Render::processInput(SDL_Event event) const
{
    //
}

Render::~Render()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
