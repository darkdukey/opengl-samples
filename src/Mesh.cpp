#include "Mesh.h"

#include <glad/glad.h>
//User headers
#include "TextureManager.h"
using namespace std;

Mesh::Mesh(
    vector<Vertex>& vertices,
    vector<uint>& indices,
    std::map<std::string, std::string>& samplerMap) {
    _vertices = vertices;
    _indices = indices;
    _graphics = make_shared<Graphics>("lit");
    for (auto& it : samplerMap) {
        _graphics->addTexture(it.first, it.second);
    }
    _graphics->createBuffer(vertices, indices);
}

void Mesh::draw(const glm::mat4& proj, const glm::mat4& view) {
    _graphics->draw(proj, view, _transform);
}
