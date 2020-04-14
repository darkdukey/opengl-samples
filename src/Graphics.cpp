#include "Graphics.h"

#include <iterator>

#include "Camera.h"
#include "ShaderManager.h"
#include "TextureManager.h"
using namespace std;

Graphics::Graphics(const string& shader_name) {
    _shader = ShaderManager::getInstance()->get(shader_name);
}

Graphics::~Graphics() {
}

void Graphics::addTexture(const std::string& name, const std::string& type) {
    if (_textures.find(name) == _textures.end()) {
        _textures[name] = TextureManager::getInstance()->get(name);
        _textureUniformMap[name] = type;
    }
}

void Graphics::draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& transform) {
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    _shader->enable();
    _shader->setMat4("transform", transform);
    _shader->setMat4("proj", proj);
    _shader->setMat4("view", view);

    int i = 0;
    for (auto& it : _textures) {
        glActiveTexture(GL_TEXTURE0 + i);
        it.second->enable(GL_TEXTURE0 + i);
        string uniform_name = _textureUniformMap[it.first];
        _shader->setInt(uniform_name, i);
        i++;
    }

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indexSize, GL_UNSIGNED_INT, 0);
}

void Graphics::createBuffer(const vector<Vertex>& vertices, const vector<uint>& indices) {
    uint VBO, EBO;
    _indexSize = indices.size();
    //TODO: do this using resource manager
    // create buffers/arrays
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(_VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
