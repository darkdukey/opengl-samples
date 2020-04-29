#pragma once

#include <glm/glm.hpp>
#include <string>

// Solid Material is for solid objects
// Check the list of solid material values here: http://devernay.free.fr/cours/opengl/materials.html
// See what the materials look like: https://learnopengl.com/Lighting/Materials
class Material {
   private:
    std::string _diffuseMap;
    std::string _specularMap;
    glm::vec3 _ambientValue;
    glm::vec3 _diffuseValue;
    glm::vec3 _specularValue;
    float _shininess;

   public:
    Material(const std::string& diffuse, const std::string& specular, float shininess);
    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);
    ~Material() {}

    std::string getDiffuseMap() const { return _diffuseMap; }
    std::string getSpecularMap() const { return _specularMap; }
    glm::vec3 getAmbientValue() const { return _ambientValue; }
    glm::vec3 getDiffuseValue() const { return _diffuseValue; }
    glm::vec3 getSpecularValue() const { return _specularValue; }
    float getShininess() const { return _shininess; }
};
