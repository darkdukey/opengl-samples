#include "Mesh.h"
//User headers
#include "TextureManager.h"
using namespace std;

Mesh::Mesh(
    vector<Vertex>& vertices,
    vector<uint>& indices) {
    _vertices = vertices;
    _indices = indices;
    _graphics = make_shared<Graphics>("lit");
    _graphics->createBuffer(vertices, indices);
}

void Mesh::setMaterial(const Material& m) {
    _graphics->setMaterial(m);
}