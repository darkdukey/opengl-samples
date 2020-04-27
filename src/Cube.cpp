#include "Cube.h"

#include <glad/glad.h>
//User headers
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "TextureManager.h"

using namespace std;

vector<Vertex> cube_vertices = {
    // positions        //Color           //texcoords
    {-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},  //fbl
    {0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},   //fbr
    {0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},    //ftl
    {-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},   //ftr
    {-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},   //bbl
    {0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},    //bbr
    {0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},     //btr
    {-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f}};   //btl

vector<uint> cube_indices =
    {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1};

shared_ptr<Cube> Cube::create(const string& shaderName) {
    return make_shared<Cube>(shaderName);
}

shared_ptr<Cube> Cube::create(const string& shaderName, const string& filename) {
    return make_shared<Cube>(shaderName, filename);
}

Cube::Cube(const string& shaderName, const string& filename) {
    _graphics = make_shared<Graphics>(shaderName);
    _graphics->addTexture(filename);
    //TODO: create buffer using buffer mananger
    _graphics->createBuffer(cube_vertices, cube_indices);
}

Cube::Cube(const string& shaderName) {
    _graphics = make_shared<Graphics>(shaderName);
    //TODO: create buffer using buffer mananger
    _graphics->createBuffer(cube_vertices, cube_indices);
}

Cube::~Cube() {
}

void Cube::setColorTint(const glm::vec3& color) {
    _graphics->setUniform("colorTint", color);
}