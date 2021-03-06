#include "./shader.hpp"
#include <glad/glad.h>
#include <iostream>

Shader::Shader(const char* vertex_source,
               const char* fragment_source,
               const char* geometry_source)
{
    unsigned int vertex_shader;
    unsigned int fragment_shader;
    unsigned int geometry_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    checkErrors(vertex_shader, "VERTEX");

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    checkErrors(fragment_shader, "FRAGMENT");

    if (geometry_source != nullptr)
    {
        geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry_shader, 1, &geometry_source, NULL);
        glCompileShader(geometry_shader);
        checkErrors(geometry_shader, "GEOMETRY");
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    if (geometry_source != nullptr)
        glAttachShader(m_id, geometry_shader);

    glLinkProgram(m_id);
    checkErrors(m_id, "PROGRAM");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if (geometry_source != nullptr)
        glDeleteShader(geometry_shader);
}

Shader::~Shader() { glDeleteProgram(m_id); }
void Shader::use() const { glUseProgram(m_id); }

void Shader::checkErrors(unsigned int object, std::string type)
{
    int success;
    char info_log[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, info_log);
            std::cerr << "ERROR::SHADER::" << type << "::Compilation failed\n"
                      << info_log << "\n";
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, info_log);
            std::cerr << "ERROR::SHADER::" << type << "::Linking failed\n"
                      << info_log << "\n";
        }
    }
}

void Shader::setInt(const std::string& name, const int value) const
{
    unsigned int location = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, const float value) const
{
    unsigned int location = glGetUniformLocation(m_id, name.c_str());
    glUniform1f(location, value);
}

void Shader::setVec3(const std::string& name, const glm::vec3 value) const
{
    unsigned int location = glGetUniformLocation(m_id, name.c_str());
    glUniform3fv(location, 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
    unsigned int location = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
