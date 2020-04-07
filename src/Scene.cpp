#include "Scene.h"

#include "Camera.h"
#include "Node.h"
Scene::Scene() {
}

Scene::~Scene() {
    _children.clear();
}

void Scene::addChild(std::shared_ptr<Node> child) {
    _children.push_back(child);
}

void Scene::addCamera(std::shared_ptr<Camera> camera) {
    _camera = camera;
}

void Scene::draw() {
    for (auto& ch : _children) {
        ch->draw(_camera->getProj(), _camera->getView());
    }
}

void Scene::update() {
    for (auto& ch : _children) {
        ch->update();
    }
}
