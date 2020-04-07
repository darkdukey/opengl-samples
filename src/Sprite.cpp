#include <glad/glad.h>
//User headers
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "Texture.h"
#include "TextureManager.h"

using namespace std;

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left
};

uint indices[] = {
    // note that we start from 0!
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

shared_ptr<Sprite> Sprite::create(const std::string& filename) {
    return make_shared<Sprite>(filename);
}

Sprite::Sprite(const string& filename) {
    _shader = ShaderManager::getInstance()->get("basic");
    //TODO: implement texture cache
    _texture = TextureManager::getInstance()->get(filename);
    _transform = glm::mat4(1.0f);
    //TODO: create buffer using buffer mananger
    createBuffer();
}

Sprite::~Sprite() {
}

void Sprite::draw(const glm::mat4& proj, const glm::mat4& view) {
    // _transform = glm::translate(glm::mat4(1.0f), glm::vec3(_x, _y, _z));
    _shader->enable();
    _shader->setMat4("transform", _transform);

    _shader->setMat4("proj", proj);
    _shader->setMat4("view", view);
    // shader.setInt("texture1", 0);
    // shader.setInt("texture2", 1);
    _texture->enable(GL_TEXTURE0);
    // texture2.enable(GL_TEXTURE1);
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::createBuffer() {
    uint VBO, EBO;
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 1. bind Vertex Array Object
    glBindVertexArray(_VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Safe to unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
