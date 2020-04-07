#include "Cube.h"

#include <glad/glad.h>
//User headers
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "TextureManager.h"

using namespace std;

float cube_vertices[] = {
    // positions        //Color           //texcoords
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f};

int cube_indices[6 * 6] =
    {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1};

Cube::Cube(const string& filename) : _x(0), _y(0), _z(0) {
    _shader = ShaderManager::getInstance()->get("basic");
    //TODO: implement texture cache
    _texture = TextureManager::getInstance()->get(filename);
    _transform = glm::mat4(1.0f);
    //TODO: create buffer using buffer mananger
    createBuffer();
}

Cube::~Cube() {
}

shared_ptr<Cube> Cube::create(const std::string& filename) {
    return make_shared<Cube>(filename);
}

void Cube::draw(const glm::mat4& proj, const glm::mat4& view) {
    _transform = glm::translate(glm::mat4(1.0f), glm::vec3(_x, _y, _z));
    _shader->enable();
    _shader->setMat4("transform", _transform);

    _shader->setMat4("proj", proj);
    _shader->setMat4("view", view);
    // shader.setInt("texture1", 0);
    // shader.setInt("texture2", 1);
    _texture->enable(GL_TEXTURE0);
    // texture2.enable(GL_TEXTURE1);
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::createBuffer() {
    uint VBO, EBO;
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 1. bind Vertex Array Object
    glBindVertexArray(_VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

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
