#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Shader
{
private:
    void checkErrors(unsigned int object, std::string type);

public:
    unsigned int m_id;

    Shader(const char* v_shader_source,
           const char* f_shader_source,
           const char* g_shader_source = nullptr);

    ~Shader();

    void use() const;

    void setInt(const std::string& name, int value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
};
