#include "Mesh.h"

#include <glad/glad.h>
//User headers
#include "TextureManager.h"
using namespace std;

Mesh::Mesh(
    vector<Vertex>& vertices,
    vector<uint>& indices,
    map<string, string>& samplerMap) {
    _vertices = vertices;
    _indices = indices;
    _graphics = make_shared<Graphics>("lit");
    for (auto& it : samplerMap) {
        _graphics->addTexture(it.first, it.second);
    }
    _graphics->createBuffer(vertices, indices);
}
