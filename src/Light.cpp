#include "Light.h"

#include <memory>

#include "Scene.h"

using namespace std;

shared_ptr<Light> Light::create(const string& name, LightType type) {
    return make_shared<Light>(name, type);
}

Light::Light(const string& name, LightType type)
    : _lightName(name),
      _lightType(type),
      _color(0.2f),
      _isInScene(false) {
}

void Light::onEnter(Scene* scene) {
    if (!_isInScene) {
        scene->addLight(Node::downcasted_shared_from_this<Light>());
        _isInScene = true;
    }
    Node::onEnter(scene);
}

void Light::onExit(Scene* scene) {
    if (_isInScene) {
        scene->removeLight(Node::downcasted_shared_from_this<Light>());
        _isInScene = false;
    }
    Node::onExit(scene);
}
