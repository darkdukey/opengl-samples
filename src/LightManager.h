#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Node.h"
#include "common.h"

enum LightType {
    Directional,
    Point,
    Spot,
    LightType_COUNT
};

class Shader;

class Light : public Node {
   private:
    std::string _lightName;
    LightType _lightType;

   public:
    Light(const std::string& name, LightType type);
    std::string getLightName() { return _lightName; }
    void setLightName(const std::string& v) { _lightName = v; }
};

//TODO: support skybox lighting
class LightManager {
   private:
    glm::vec3 _ambientColor;
    float _ambientStrength;
    std::unordered_map<LightType, uint> _lightTypeMap;
    std::vector<std::shared_ptr<Light>> _lights;

   public:
    const std::string NameDirectional = "directional";
    const std::string NamePoint = "point";
    const std::string NameSpot = "spot";
    const std::string NameAmbientColor = "ambientColor";

   public:
    LightManager();
    ~LightManager();

    void setAmbientColor(glm::vec3 color) { _ambientColor = color; }
    std::shared_ptr<Light> getLight(LightType type);
    void releaseLight(std::shared_ptr<Light> light);

    glm::vec3 getAmbientColor() { return _ambientColor * _ambientStrength; }
};