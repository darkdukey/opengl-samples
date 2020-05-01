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
    _lights.insert(light);

    switch (light->type()) {
        case Directional:
            _directLights.insert(light);
            break;
        case Point:
            _pointLights.insert(light);
            break;
        case Spot:
            _spotLights.insert(light);
            break;
        default:
            LOG(error) << "Unsupported light type";
            break;
    }
}

void LightManager::doRemove(set<shared_ptr<Light>>& arr, shared_ptr<Light> light) {
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

        // Directional Light
        int i = 0;
        for (auto l : _directLights) {
            string str_uniform = NameDirectional + "[" + to_string(i) + "]";
            shader->setVec3(str_uniform + ".pos", l->pos());
            shader->setVec3(str_uniform + ".ambient", l->amb());
            shader->setVec3(str_uniform + ".diffuse", l->diff());
            shader->setVec3(str_uniform + ".specular", l->spec());
            i++;
            if (i >= count) break;
        }
        shader->setInt(NameDirectional + "Count", count);

        //Point/Spot Light
        count = min((int)_pointLights.size(), MAX_Point_Light);
        i = 0;
        for (auto l : _pointLights) {
            string str_uniform = NamePoint + "[" + to_string(i) + "]";
            shader->setVec3(str_uniform + ".pos", l->worldPos());
            shader->setVec3(str_uniform + ".ambient", l->amb());
            shader->setVec3(str_uniform + ".diffuse", l->diff());
            shader->setVec3(str_uniform + ".specular", l->spec());
            shader->setFloat(str_uniform + ".constant", l->cst());
            shader->setFloat(str_uniform + ".linear", l->lin());
            shader->setFloat(str_uniform + ".quadratic", l->quad());
            i++;
            if (i >= count) break;
        }
        shader->setInt(NamePoint + "Count", count);
    }
}