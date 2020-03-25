#include "Scene.h"
#include "Camera.h"
#include "Sprite.h"
Scene::Scene() {
}

Scene::~Scene() {
    _children.clear();
}

void Scene::addChild(std::shared_ptr<Sprite> child) {
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