#include "Scene.h"

#include "Camera.h"
#include "Node.h"
#include "Renderer.h"
using namespace std;

shared_ptr<Scene> Scene::create() {
    return make_shared<Scene>();
}

Scene::Scene() {
    _root = Node::create();
}

Scene::~Scene() {
}

void Scene::addChild(shared_ptr<Node> node) {
    _root->addChild(node);
    node->onAddToScene(this);
}

void Scene::removeChild(std::shared_ptr<Node> node) {
    node->onRemoveFromScene(this);
    _root->removeChild(node);
}
void Scene::update() {
    _root->update();
}
void Scene::draw() {
    _root->draw();
    Renderer::getInstance()->draw(_camera, &_lightManager);
}

void Scene::addCamera(shared_ptr<Camera> camera) {
    _camera = camera;
}

void Scene::removeCamera(std::shared_ptr<Camera> camera) {
    _camera = nullptr;
}
void Scene::addLight(shared_ptr<Light> light) {
    //TODO: find a way to integrate this logic into scene graph
    _lightManager.addLight(light);
}

void Scene::removeLight(shared_ptr<Light> light) {
    _lightManager.removeLight(light);
}