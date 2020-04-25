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
      _color(0.2f) {
}

void Light::onAddToScene(Scene* scene) {
    scene->addLight(Node::downcasted_shared_from_this<Light>());
    Node::onAddToScene(scene);
}

void Light::onRemoveFromScene(Scene* scene) {
    scene->removeLight(Node::downcasted_shared_from_this<Light>());
    Node::onRemoveFromScene(scene);
}
