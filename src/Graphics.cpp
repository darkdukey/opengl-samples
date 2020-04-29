#include "Graphics.h"

#include <iterator>

#include "Renderer.h"
#include "TextureManager.h"
using namespace std;

Graphics::Graphics(const string& shader_name)
    : _VAO(0),
      _indexSize(0) {
    _cmd = Renderer::getInstance()->getCmd();
    _cmd->setShaderName(shader_name);
    setMaterial({{0.25f, 0.20725f, 0.20725f}, {1.0f, 0.829f, 0.829f}, {0.296648f, 0.296648f, 0.296648f}, 11.26f});
}

Graphics::~Graphics() {
}

void Graphics::addTexture(const string& name, const string& type) {
    if (_textures.find(name) == _textures.end()) {
        _textures[name] = TextureManager::getInstance()->get(name);
        _textureUniformMap[name] = type;
    }
}

void Graphics::draw(const glm::mat4& transform) {
    _cmd->setTransform(transform);
    _cmd->setTextureUniform(_textureUniformMap);
    _cmd->setVAO(_VAO);
    _cmd->setCount(_indexSize);
    _cmd->setUniform(_vec3Map);
    _cmd->setUniform(_floatMap);
}

void Graphics::createBuffer(const vector<Vertex>& vertices, const vector<uint>& indices) {
    //TODO: move buffer logic to renderer
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

void Graphics::setUniform(const string& name, glm::vec3 value) {
    _vec3Map[name] = value;
}

void Graphics::setUniform(const std::string& name, float value) {
    _floatMap[name] = value;
}

void Graphics::setMaterial(const Material& m) {
    if (!m.getDiffuseMap().empty()) {
        addTexture(m.getDiffuseMap(), "material.diffuseMap");
    } else {
        setUniform("material.ambientValue", m.getAmbientValue());
        setUniform("material.diffuseValue", m.getDiffuseValue());
        setUniform("material.specularValue", m.getSpecularValue());
    }

    if (!m.getSpecularMap().empty()) {
        addTexture(m.getSpecularMap(), "material.specularMap");
    }

    setUniform("material.shininess", m.getShininess());
}
