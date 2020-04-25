#include "Node.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

shared_ptr<Node> Node::create() {
    return make_shared<Node>();
}

Node::Node()
    : _graphics(nullptr),
      _pos(0),
      _rot(0),
      _scale(1),
      _scene(nullptr) {
    _transform = glm::mat4(1.0f);
}

Node::~Node() {
    _children.clear();
}

void Node::update() {
    _transform = glm::translate(glm::mat4(1.0f), _pos);
    _transform = glm::rotate(_transform, glm::radians(_rot.x), glm::vec3(1, 0, 0));
    _transform = glm::rotate(_transform, glm::radians(_rot.y), glm::vec3(0, 1, 0));
    _transform = glm::rotate(_transform, glm::radians(_rot.z), glm::vec3(0, 0, 1));
    _transform = glm::scale(_transform, _scale);

    auto parent = getParent();
    if (parent != nullptr) {
        _transform = parent->getTransform() * _transform;
    }

    for (auto& c : _children) {
        c->update();
    }
}

void Node::onAddToScene(Scene* scene) {
    _scene = scene;
    for (auto ch : _children) {
        ch->onAddToScene(scene);
    }
}

void Node::onRemoveFromScene(Scene* scene) {
    for (auto ch : _children) {
        ch->onRemoveFromScene(scene);
    }
    _scene = nullptr;
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
    if (_scene) {
        onAddToScene(_scene);
    }
}

void Node::removeChild(shared_ptr<Node> child) {
    auto pos = find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
        child->setParent(nullptr);
        if (_scene) {
            onRemoveFromScene(_scene);
        }
    }
}
