#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include "Light.h"
#include "Node.h"
#include "common.h"

class Shader;
//TODO: support skybox lighting
class LightManager {
   private:
    std::set<std::shared_ptr<Light>> _lights;
    std::set<std::shared_ptr<Light>> _directLights;
    std::set<std::shared_ptr<Light>> _pointLights;
    std::set<std::shared_ptr<Light>> _spotLights;

   private:
    void doRemove(std::set<std::shared_ptr<Light>>& arr, std::shared_ptr<Light> light);

   public:
    const std::string NameDirectional = "directLight";
    const std::string NamePoint = "pointLight";
    const std::string NameSpot = "spotLight";
    const int MAX_Direct_Light = 2;
    const int MAX_Point_Light = 6;
    const int MAX_Spot_Light = 6;

   public:
    LightManager();
    ~LightManager();

    void add(std::shared_ptr<Light> light);
    void remove(std::shared_ptr<Light> light);
    void clear();
    void draw(Shader* shader);
};