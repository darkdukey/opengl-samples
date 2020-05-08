#include "Sprite.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "TextureManager.h"

using namespace std;

vector<Vertex> vertices = {
    // positions          // colors           // texture coords
    {0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},    // top right
    {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},   // bottom right
    {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},  // bottom left
    {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}    // top left
};

vector<uint> indices = {
    // note that we start from 0!
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

shared_ptr<Sprite> Sprite::create(const string& filename) {
    return make_shared<Sprite>(filename);
}

Sprite::Sprite(const string& filename) {
    _graphics = make_shared<Graphics>("basic");
    _graphics->addTexture(filename, "texture0");
    //TODO: create buffer using buffer mananger
    _graphics->createBuffer(vertices, indices);
}

Sprite::~Sprite() {
}