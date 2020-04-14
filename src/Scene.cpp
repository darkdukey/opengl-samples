#include "Scene.h"

#include "Camera.h"
#include "Node.h"

using namespace std;

shared_ptr<Scene> Scene::create() {
    return make_shared<Scene>();
}

Scene::Scene() {
}

Scene::~Scene() {
    _children.clear();
}

void Scene::addCamera(shared_ptr<Camera> camera) {
    _camera = camera;
}

void Scene::draw() {
    for (auto& ch : _children) {
        ch->draw(_camera->getProj(), _camera->getView());
    }
}
