#include "Light.h"

#include <memory>

#include "Cube.h"
#include "Debug.h"
#include "Scene.h"

using namespace std;
using namespace NT;

shared_ptr<Light> Light::create(const string& name, LightType type) {
    return make_shared<Light>(name, type);
}

Light::Light(const string& name, LightType type)
    : _lightName(name),
      _lightType(type),
      _ambient(0),
      _diffuse(1),
      _specular(1),
      _constant(1.0f),
      _linear(0.09f),
      _quadratic(0.032f),
      _cutOff(glm::cos(glm::radians(12.5f))),
      _outerCutOff(glm::cos(glm::radians(17.5f))),
      _hasDebugShape(false) {
}

void Light::onAddToScene(Scene* scene) {
    LOG(debug) << "Add Light: " << _lightName;
    scene->addLight(Node::downcasted_shared_from_this<Light>());
    Node::onAddToScene(scene);
}

void Light::onRemoveFromScene(Scene* scene) {
    scene->removeLight(Node::downcasted_shared_from_this<Light>());
    Node::onRemoveFromScene(scene);
}

void Light::enableDebugShape() {
    if (!_hasDebugShape) {
        _hasDebugShape = true;
        auto cube = Cube::create("solid_unlit");
        cube->setColorTint(_diffuse);
        addChild(cube);
    }
}