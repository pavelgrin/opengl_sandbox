#pragma once

class Shader;
class Texture2D;

Shader* loadShader(const char* vertex_shader_file,
                   const char* fragment_shader_file,
                   const char* geometry_shader_file = nullptr);

Texture2D* loadTexture(const char* file, const bool alpha);
