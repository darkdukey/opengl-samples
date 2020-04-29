#include "LitCube.h"

#include "Material.h"

using namespace std;

vector<Vertex> lit_cube_vertices = {
    // positions        //Normal           //texcoords
    {-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0, 0},
    {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0, 1},
    {0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1, 1},
    {0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1, 0},
    {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0, 0},
    {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0, 1},
    {0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1, 1},
    {0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1, 0},
    {0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0, 0},
    {0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0, 1},
    {0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1, 1},
    {0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1, 0},
    {-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0, 0},
    {-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0, 1},
    {-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1, 1},
    {-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1, 0},
    {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0, 0},
    {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0, 1},
    {0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1, 1},
    {0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1, 0},
    {-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0, 0},
    {-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0, 1},
    {0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1, 1},
    {0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1, 0}};

vector<uint> lit_cube_indices =
    {
        0, 1, 3,
        3, 1, 2,
        4, 5, 7,
        7, 5, 6,
        8, 9, 11,
        11, 9, 10,
        12, 13, 15,
        15, 13, 14,
        16, 17, 19,
        19, 17, 18,
        20, 21, 23,
        23, 21, 22};

shared_ptr<LitCube> LitCube::create(const string& shaderName) {
    return make_shared<LitCube>(shaderName);
}

LitCube::LitCube(const string& shaderName) {
    _graphics = make_shared<Graphics>(shaderName);
    _graphics->createBuffer(lit_cube_vertices, lit_cube_indices);
}

LitCube::~LitCube() {
}

void LitCube::setMaterial(const Material& m) {
    _graphics->setMaterial(m);
}