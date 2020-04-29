
#include "Material.h"

#include "Graphics.h"

using namespace std;

Material::Material(const string& diffuse, const string& specular, float shininess)
    : _diffuseMap(diffuse),
      _specularMap(specular),
      _shininess(shininess) {
}

Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
    : _ambientValue(ambient),
      _diffuseValue(diffuse),
      _specularValue(specular),
      _shininess(shininess) {
}