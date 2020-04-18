#pragma once

#include <assimp/scene.h>

#include <string>

#include "Node.h"

class Model : public Node {
   public:
    /*  Functions   */
    static std::shared_ptr<Model> create(const std::string &filename);
    Model(const std::string &path);
    void load();

   private:
    /*  Model Data  */
    std::string _path;
    std::string _modelDir;

    /*  Functions   */
    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    void processMesh(aiMesh *mesh, const aiScene *scene);
    void loadMaterialTextures(std::map<std::string, std::string> &samplerMap, aiMaterial *mat, aiTextureType type, std::string typeName);
};
