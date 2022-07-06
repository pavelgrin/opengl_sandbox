#include "./model.hpp"
#include "../loaders/loaders.hpp"
#include "./mesh.hpp"
#include "./texture.hpp"

Model::Model(const std::string textures_dir, const aiScene* scene)
    : m_textures_dir(textures_dir)
{
    processNode(scene->mRootNode, scene);
}

Model::~Model()
{
    // TODO: Delete mesh pointers
}

void Model::draw(Shader* shader)
{
    for (unsigned int i = 0; i < meshes.size(); ++i)
    {
        meshes[i]->draw(shader);
    }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    glm::vec3 vec3;
    glm::vec2 vec2;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;

        vec3.x = mesh->mVertices[i].x;
        vec3.y = mesh->mVertices[i].y;
        vec3.z = mesh->mVertices[i].z;

        vertex.position = vec3;

        if (mesh->HasNormals())
        {
            vec3.x = mesh->mNormals[i].x;
            vec3.y = mesh->mNormals[i].y;
            vec3.z = mesh->mNormals[i].z;

            vertex.normal = vec3;
        }

        if (mesh->mTextureCoords[0])
        {
            vec2.x            = mesh->mTextureCoords[0][i].x;
            vec2.y            = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec2;
        }
        else
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuse_maps  = loadTextures(material, aiTextureType_DIFFUSE);
        std::vector<Texture> specular_maps = loadTextures(material, aiTextureType_SPECULAR);

        textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
        textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
    }

    return new Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadTextures(aiMaterial* material, aiTextureType type)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); ++i)
    {
        aiString file_name;
        material->GetTexture(type, i, &file_name);

        std::string file_path = m_textures_dir + std::string(file_name.C_Str());

        bool skip = false;
        for (unsigned int j = 0; j < m_loaded_textures.size(); ++j)
        {
            if (m_loaded_textures[j].path == file_path)
            {
                textures.push_back(m_loaded_textures[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            Texture texture;

            texture.name    = getTextureName(type);
            texture.texture = getTexture(file_path);
            texture.path    = file_path;

            textures.push_back(texture);
            m_loaded_textures.push_back(texture);
        }
    }

    return textures;
}

std::string Model::getTextureName(aiTextureType type)
{
    std::string shader_name = "material.";
    std::string deffuse     = "texture_diffuse";
    std::string specular    = "texture_specular";

    switch (type)
    {
    case aiTextureType_DIFFUSE:
        shader_name += deffuse;
        break;
    case aiTextureType_SPECULAR:
        shader_name += specular;
        break;
    default:
        shader_name += deffuse;
        break;
    }

    return shader_name;
}

Texture2D* Model::getTexture(std::string file_path)
{
    return loadTexture(file_path);
}
