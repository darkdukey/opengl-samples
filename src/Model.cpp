#include "Model.h"

#include <assimp/postprocess.h>

#include <assimp/Importer.hpp>
#include <map>
#include <memory>

#include "Debug.h"
#include "FileUtil.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include "TextureManager.h"
using namespace std;
using namespace NT;

shared_ptr<Model> Model::create(const string &filename) {
    return make_shared<Model>(filename);
}

Model::Model(const string &path) : _path(path) {
}

void Model::load() {
    loadModel(_path);
}

void Model::loadModel(const string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOG(error) << "Load Model: " << importer.GetErrorString();
        return;
    }
    _modelDir = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process all the node's meshes (if any)
    for (uint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }
    // then do the same for each of its children
    for (uint i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    // data to fill
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    // Walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;  // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if (mesh->mTextureCoords[0])  // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // TODO: support normal map
    // TODO: support height map

    // return a mesh object created from the extracted mesh data
    string diffuseMap = getTexture(material, aiTextureType_DIFFUSE);
    string specularMap = getTexture(material, aiTextureType_SPECULAR);
    // TODO: find out shininess value from model file
    Material mat(diffuseMap, specularMap, 32.0f);
    auto m = make_shared<Mesh>(vertices, indices);
    m->setMaterial(mat);
    addChild(m);
}

string Model::getTexture(aiMaterial *mat, aiTextureType type) {
    string img_path;
    auto count = mat->GetTextureCount(type);
    for (unsigned int i = 0; i < count; i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        //Make sure the texture path is under model folder
        img_path = FileUtil::join(_modelDir, str.C_Str());
        LOG(debug) << img_path << i;
    }
    return img_path;
}
