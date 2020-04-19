#include "Scene.h"

#include "Camera.h"
#include "Node.h"
#include "Renderer.h"
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
    for (auto ch : _children) {
        ch->draw();
    }
    Renderer::getInstance()->draw(_camera, &_lightManager);
}

void Scene::addLight(std::shared_ptr<Light> light) {
    //TODO: find a way to integrate this logic into scene graph
    _lightManager.addLight(light);
}