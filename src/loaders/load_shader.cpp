#include "../render/shader.hpp"
#include "./loaders.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader* loadShader(const char* vertex_shader_file,
                   const char* fragment_shader_file,
                   const char* geometry_shader_file)
{
    std::string v_shader_code;
    std::string f_shader_code;
    std::string g_shader_code;

    try
    {
        std::ifstream v_shader_file(vertex_shader_file);
        std::ifstream f_shader_file(fragment_shader_file);

        std::stringstream v_shader_stream;
        std::stringstream f_shader_stream;

        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();

        v_shader_file.close();
        f_shader_file.close();

        v_shader_code = v_shader_stream.str();
        f_shader_code = f_shader_stream.str();

        if (geometry_shader_file != nullptr)
        {
            std::ifstream g_shader_file(geometry_shader_file);
            std::stringstream g_shader_stream;

            g_shader_stream << g_shader_file.rdbuf();
            g_shader_file.close();
            g_shader_code = g_shader_stream.str();
        }
    }
    catch (std::exception e)
    {
        std::cerr << "ERROR::SHADER::File not succesfully read\n"
                  << e.what() << "\n";

        return nullptr;
    }

    const char* v_shader_source = v_shader_code.c_str();
    const char* f_shader_source = f_shader_code.c_str();
    const char* g_shader_source = geometry_shader_file ? g_shader_code.c_str()
                                                       : nullptr;

    return new Shader(v_shader_source, f_shader_source, g_shader_source);
}
