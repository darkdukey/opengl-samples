#include "LightManager.h"

#include <algorithm>

#include "Debug.h"
#include "Graphics.h"
#include "Shader.h"

using namespace std;
using namespace NT;

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

    switch (type) {
        case Directional:
            _directLights.push_back(light);
            break;
        case Point:
            _pointLights.push_back(light);
            break;
        case Spot:
            _spotLights.push_back(light);
            break;
        default:
            LOG(error) << "Unsupported light type";
            break;
    }

    return light;
}

void LightManager::releaseLight(shared_ptr<Light> light) {
    auto pos = find(_lights.begin(), _lights.end(), light);
    if (pos != _lights.end()) {
        _lights.erase(pos);
    }
}

void LightManager::drawLights(Shader* shader) {
    if (shader) {
        // Ambient Color
        shader->setVec3(NameAmbientColor, getAmbientColor());

        vector<glm::vec3> pos;
        vector<glm::vec3> color;
        int count;
        if (_directLights.size() >= MAX_Direct_Light) {
            LOG(warning) << "max direct light: " << MAX_Direct_Light << " count: " << _directLights.size();
        }

        count = min((int)_directLights.size(), MAX_Direct_Light);

        // Diffuse/Point/Spot light
        for (int i = 0; i < count; i++) {
            auto l = _directLights[i];
            pos.push_back(l->getPos());
            color.push_back(l->getColor());
        }

        shader->setVec3Array(NameDirectional + "Pos", pos);
        shader->setVec3Array(NameDirectional + "Color", color);
        shader->setInt(NameDirectional + "Count", count);
    }
}