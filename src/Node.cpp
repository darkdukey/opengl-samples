#include "Node.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

std::shared_ptr<Node> Node::create() {
    return make_shared<Node>();
}

Node::Node()
    : _graphics(nullptr),
      _x(0),
      _y(0),
      _z(0),
      _rotX(0),
      _rotY(0),
      _rotZ(0),
      _scaleX(1),
      _scaleY(1),
      _scaleZ(1) {
    _transform = glm::mat4(1.0f);
}

Node::~Node() {
    _children.clear();
}

void Node::update() {
    _transform = glm::translate(glm::mat4(1.0f), glm::vec3(_x, _y, _z));
    _transform = glm::rotate(_transform, glm::radians(_rotX), glm::vec3(1, 0, 0));
    _transform = glm::rotate(_transform, glm::radians(_rotY), glm::vec3(0, 1, 0));
    _transform = glm::rotate(_transform, glm::radians(_rotZ), glm::vec3(0, 0, 1));
    _transform = glm::scale(_transform, glm::vec3(_scaleX, _scaleY, _scaleZ));

    auto parent = getParent();
    if (parent != nullptr) {
        _transform = parent->getTransform() * _transform;
    }

    for (auto& c : _children) {
        c->update();
    }
}

void Node::draw() {
    if (_graphics != nullptr) {
        _graphics->draw(_transform);
    }

    for (auto& c : _children) {
        c->draw();
    }
}

void Node::addChild(shared_ptr<Node> child) {
    child->setParent(shared_from_this());
    _children.push_back(child);
}

void Node::removeChild(shared_ptr<Node> child) {
    auto pos = find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
        child->setParent(nullptr);
    }
}
