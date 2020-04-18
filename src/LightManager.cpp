#include "LightManager.h"

#include <algorithm>

#include "Debug.h"
#include "Graphics.h"
#include "Shader.h"

using namespace std;
using namespace NT;

Light::Light(const std::string& name, LightType type)
    : _lightName(name), _lightType(type) {
    //
}

LightManager::LightManager() {
    _ambientColor = {1.0f, 0.5f, 0.31f};
    _ambientStrength = 0.2f;
    _lightTypeMap[Directional] = 0;
    _lightTypeMap[Point] = 0;
    _lightTypeMap[Spot] = 0;
}

LightManager::~LightManager() {
    _lights.clear();
}

shared_ptr<Light> LightManager::getLight(LightType type) {
    string name = "";
    switch (type) {
        case Directional:
            name = NameDirectional;
            break;
        case Point:
            name = NamePoint;
            break;
        case Spot:
            name = NameSpot;
            break;
        default:
            LOG(error) << "Unsupported light type";
            break;
    }

    if (type < LightType_COUNT) {
        name += _lightTypeMap[type];
        _lightTypeMap[type]++;
    }

    auto light = make_shared<Light>(name, type);
    _lights.push_back(light);

    return light;
}

void LightManager::releaseLight(shared_ptr<Light> light) {
    auto pos = find(_lights.begin(), _lights.end(), light);
    if (pos != _lights.end()) {
        _lights.erase(pos);
    }
}
