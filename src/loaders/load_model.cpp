#include "../render/model.hpp"
#include "./loaders.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

Model* loadModel(const std::string file, const std::string textures_dir)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(file, aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::File not succesfully read\n"
                  << import.GetErrorString() << "\n";
        return nullptr;
    }

    return new Model(textures_dir, scene);
}
