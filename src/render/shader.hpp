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

    void setInt(const std::string& name, const int value) const;
    void setFloat(const std::string& name, const float value) const;
    void setVec3(const std::string& name, const glm::vec3 value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
};
