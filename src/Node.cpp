#include "Node.h"

#include <glm/gtc/matrix_transform.hpp>

Node::Node() : _x(0), _y(0), _z(0), _rotX(0), _rotY(0), _rotZ(0), _scaleX(1), _scaleY(1), _scaleZ(1) {
    _transform = glm::mat4(1.0f);
}

Node::~Node() {
}

void Node::update() {
    _transform = glm::translate(glm::mat4(1.0f), glm::vec3(_x, _y, _z));
    _transform = glm::rotate(_transform, glm::radians(_rotX), glm::vec3(1, 0, 0));
    _transform = glm::rotate(_transform, glm::radians(_rotY), glm::vec3(0, 1, 0));
    _transform = glm::rotate(_transform, glm::radians(_rotZ), glm::vec3(0, 0, 1));
    _transform = glm::scale(_transform, glm::vec3(_scaleX, _scaleY, _scaleZ));
}
