#pragma once

#include <assimp/scene.h>
#include <string>
#include <vector>

class Shader;
class Mesh;
class Texture2D;
struct Texture;

class Model
{
public:
    Model(const std::string directory, const aiScene* scene);
    ~Model();

    void draw(Shader* shader);

private:
    std::vector<Mesh*> meshes;
    std::string m_textures_dir;
    std::vector<Texture> m_loaded_textures;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture> loadTextures(aiMaterial* material, aiTextureType type);

    std::string getTextureName(aiTextureType type);
    Texture2D* getTexture(std::string file);
};
