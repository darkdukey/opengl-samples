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
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

    //Attenuation
    float _constant;
    float _linear;
    float _quadratic;

    //Spot light
    float _cutOff;
    float _outerCutOff;

    //Debug
    bool _hasDebugShape;

   public:
    static std::shared_ptr<Light> create(const std::string& name, LightType type);
    Light(const std::string& name, LightType type);
    void onAddToScene(Scene* scene) override;
    void onRemoveFromScene(Scene* scene) override;
    void enableDebugShape();

    std::string getLightName() { return _lightName; }
    void setLightName(const std::string& v) { _lightName = v; }
    void samb(const glm::vec3& v) { _ambient = v; }
    glm::vec3 amb() { return _ambient; }
    void sdiff(const glm::vec3& v) { _diffuse = v; }
    glm::vec3 diff() { return _diffuse; }
    void sspec(const glm::vec3& v) { _specular = v; }
    glm::vec3 spec() { return _specular; }
    LightType type() { return _lightType; }
    float cst() { return _constant; }
    float lin() { return _linear; }
    float quad() { return _quadratic; }
    void scut(float v) { _cutOff = v; }
    float cut() { return _cutOff; }
    void socut(float v) { _outerCutOff = v; }
    float ocut() { return _outerCutOff; }
};
