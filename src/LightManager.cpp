#include "LightManager.h"

#include <algorithm>

#include "Debug.h"
#include "Graphics.h"
#include "Shader.h"

using namespace std;
using namespace NT;

LightManager::LightManager() {
}

LightManager::~LightManager() {
    _lights.clear();
}

void LightManager::addLight(shared_ptr<Light> light) {
    _lights.push_back(light);

    switch (light->type()) {
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

void LightManager::doRemove(vector<shared_ptr<Light>>& arr, shared_ptr<Light> light) {
    auto pos = find(arr.begin(), arr.end(), light);
    if (pos != arr.end()) {
        arr.erase(pos);
    }
}

void LightManager::removeLight(shared_ptr<Light> light) {
    doRemove(_lights, light);
    switch (light->type()) {
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
        int count;

        if (_directLights.size() >= MAX_Direct_Light) {
            LOG(warning) << "max direct light: " << MAX_Direct_Light << " count: " << _directLights.size();
        }

        count = min((int)_directLights.size(), MAX_Direct_Light);

        // Directional
        for (int i = 0; i < count; i++) {
            auto l = _directLights[i];
            string str_uniform = NameDirectional + "[" + to_string(i) + "]";
            shader->setVec3(str_uniform + ".pos", l->pos());
            shader->setVec3(str_uniform + ".ambient", l->amb());
            shader->setVec3(str_uniform + ".diffuse", l->diff());
            shader->setVec3(str_uniform + ".specular", l->spec());
        }

        shader->setInt(NameDirectional + "Count", count);

        //Point/Spot light
        count = min((int)_pointLights.size(), MAX_Point_Light);
        for (int i = 0; i < count; i++) {
            auto l = _pointLights[i];
            string str_uniform = NamePoint + "[" + to_string(i) + "]";
            shader->setVec3(str_uniform + ".pos", l->worldPos());
            shader->setVec3(str_uniform + ".ambient", l->amb());
            shader->setVec3(str_uniform + ".diffuse", l->diff());
            shader->setVec3(str_uniform + ".specular", l->spec());
        }

        shader->setInt(NamePoint + "Count", count);
    }
}