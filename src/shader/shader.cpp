#include "./shader.hpp"

void Shader::init(const char* vertex_path, const char* fragment_path)
{
    std::ifstream v_shader_file;
    std::ifstream f_shader_file;

    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string v_shader_string;
    std::string f_shader_string;

    try
    {
        v_shader_file.open(vertex_path);
        f_shader_file.open(fragment_path);

        std::stringstream v_shader_stream;
        std::stringstream f_shader_stream;

        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();

        v_shader_file.close();
        f_shader_file.close();

        v_shader_string = v_shader_stream.str();
        f_shader_string = f_shader_stream.str();
    }
    catch (const std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n"
                  << e.what() << "\n";
    }

    const char* vertex_shader_source   = v_shader_string.c_str();
    const char* fragment_shader_source = f_shader_string.c_str();

    // -------------------------------------------------------------------------
    int success;
    char info_log[512];

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << info_log << "\n";
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << info_log << "\n";
    }

    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader);
    glAttachShader(m_program_id, fragment_shader);
    glLinkProgram(m_program_id);

    glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_program_id, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << info_log << "\n";
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use() const { glUseProgram(m_program_id); }

Shader::~Shader() { glDeleteProgram(m_program_id); }