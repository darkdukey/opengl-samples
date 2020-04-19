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
}

LightManager::~LightManager() {
    _lights.clear();
}

void LightManager::addLight(std::shared_ptr<Light> light) {
    _lights.push_back(light);

    switch (light->getLightType()) {
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
}

void LightManager::doRemove(std::vector<std::shared_ptr<Light>>& arr, std::shared_ptr<Light> light) {
    auto pos = find(arr.begin(), arr.end(), light);
    if (pos != arr.end()) {
        arr.erase(pos);
    }
}

void LightManager::removeLight(shared_ptr<Light> light) {
    doRemove(_lights, light);
    switch (light->getLightType()) {
        case Directional:
            doRemove(_directLights, light);
            break;
        case Point:
            doRemove(_pointLights, light);
            break;
        case Spot:
            doRemove(_spotLights, light);
            break;
        default:
            LOG(error) << "Unsupported light type";
            break;
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
            pos.push_back(l->getPosition());
            color.push_back(l->getColor());
        }

        shader->setVec3Array(NameDirectional + "Pos", pos);
        shader->setVec3Array(NameDirectional + "Color", color);
        shader->setInt(NameDirectional + "Count", count);
    }
}