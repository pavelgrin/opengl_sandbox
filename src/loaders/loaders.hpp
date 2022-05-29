#pragma once

#include <string>

class Shader;
class Texture2D;
class Model;

Shader* loadShader(const std::string vertex_shader_file,
                   const std::string fragment_shader_file,
                   const std::string geometry_shader_file = "");

Texture2D* loadTexture(const std::string file);

Model* loadModel(const std::string file, const std::string textures_dir);
