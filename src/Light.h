#pragma once

#include <memory>
#include <string>

#include "Node.h"

enum LightType {
    Directional,
    Point,
    Spot,
    LightType_COUNT
};

class Light : public Node {
   private:
    std::string _lightName;
    LightType _lightType;
    glm::vec3 _color;

   public:
    static std::shared_ptr<Light> create(const std::string& name, LightType type);
    Light(const std::string& name, LightType type) : _lightName(name), _lightType(type), _color(0.2f) {}
    std::string getLightName() { return _lightName; }
    void setLightName(const std::string& v) { _lightName = v; }
    void setColor(float r, float g, float b) {
        _color.r = r;
        _color.g = g;
        _color.b = b;
    }
    glm::vec3 getColor() { return _color; }
    LightType getLightType() { return _lightType; }
};
